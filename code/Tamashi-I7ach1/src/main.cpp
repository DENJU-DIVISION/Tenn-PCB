#include <Arduino.h>
#include <FastLED.h>
#define LED_Pin 20
#define LED_Type WS2812
#define LINE_L 4
#define LINE_R 21
#define FRONT_L 2
#define FRONT_R 1
#define DIAG_L 3 
#define DIAG_R 0
#define MR1 7
#define MR2 10
#define ML1 5
#define ML2 6
#define PWM_MR1 0
#define PWM_MR2 1
#define PWM_ML1 2
#define PWM_ML2 3
#define STRAT_SW 8
#define START 9
#define freq 1000

CRGB leds[2]; 
byte strat = 0;

void setup() {                
  //defining output of the LEDs and type of LED
  pinMode(LED_Pin, OUTPUT);
  FastLED.addLeds<LED_Type, LED_Pin, RGB>(leds, 2).setCorrection(TypicalLEDStrip);
  //defining inputs for sensors and buttons
  pinMode(LINE_L, INPUT);
  pinMode(LINE_R, INPUT);
  pinMode(FRONT_L ,INPUT);
  pinMode(FRONT_R ,INPUT);
  pinMode(DIAG_L ,INPUT);
  pinMode(DIAG_R ,INPUT);
  pinMode(STRAT_SW ,INPUT);
  pinMode(START ,INPUT);
  //defining PWM channels for the motors
  ledcSetup(PWM_MR1, freq, 8);
  ledcSetup(PWM_MR2, freq, 8);
  ledcSetup(PWM_ML1, freq, 8);
  ledcSetup(PWM_ML2, freq, 8);
  //attaching PWM channel to the respective motors
  ledcAttachPin(MR1, PWM_MR1);
  ledcAttachPin(MR2, PWM_MR2);
  ledcAttachPin(ML1, PWM_ML1);
  ledcAttachPin(ML2, PWM_ML2);
}

byte SensState(){
  //sends a numeric value from 0 to 15 depending on the number of sensors detecting
  bool sens1 = !digitalRead(FRONT_L);
  byte sens2 = !digitalRead(FRONT_R)*2;
  byte sens3 = digitalRead(DIAG_L)*4;
  byte sens4 = digitalRead(DIAG_R)*8;
  byte total = sens1 + sens2 + sens3 + sens4;
  return total;
}

byte LineState(){
  //sends a numeric value from 0 to 3 depending on the number of sensors detecting
  bool line1 = digitalRead(LINE_L);
  byte line2 = digitalRead(LINE_R)*2;
  byte total = line1 + line2;
  return total;
}

//functions for the control of the motors, a and b can be values from 0 to 255 to adjust the speed of the motors and t is the time
void Foward(byte a, byte b, int t){
  ledcWrite(PWM_MR1, a);
  ledcWrite(PWM_MR2, 0);
  ledcWrite(PWM_ML1, b);
  ledcWrite(PWM_ML2, 0);
  delay(t);
}

void Backwards(byte a, byte b, int t){
  ledcWrite(PWM_MR1, 0);
  ledcWrite(PWM_MR2, a);
  ledcWrite(PWM_ML1, 0);
  ledcWrite(PWM_ML2, b);
  delay(t);
}

void Right(byte a, byte b, int t){
  ledcWrite(PWM_MR1, 0);
  ledcWrite(PWM_MR2, a);
  ledcWrite(PWM_ML1, b);
  ledcWrite(PWM_ML2, 0);
  delay(t);
}

void Left(byte a, byte b, int t){
  ledcWrite(PWM_MR1, a);
  ledcWrite(PWM_MR2, 0);
  ledcWrite(PWM_ML1, 0);
  ledcWrite(PWM_ML2, b);
  delay(t);
}

void MotorOff(int t){
  ledcWrite(PWM_MR1, 0);
  ledcWrite(PWM_MR2, 0);
  ledcWrite(PWM_ML1, 0);
  ledcWrite(PWM_ML2, 0);
  delay(t);
}

void Brake(int t){
  ledcWrite(PWM_MR1, 255);
  ledcWrite(PWM_MR2, 255);
  ledcWrite(PWM_ML1, 255);
  ledcWrite(PWM_ML2, 255);
  delay(t);
}

void Main_Battle(){
  while(LineState()==3){
    switch (SensState()){
    case 1:
      /* code */
      break;
          
    case 2:

      break;

    case 3:
      Foward(255,255,10);
      break;

    default:
      break;
    }
  }
  if (LineState()==1){
   //code 
  }
  else if(LineState()==2){
    //code
  }
}

void loop(){
  if(digitalRead(STRAT_SW==HIGH)){  //increases value of strat each time the STRAT button is pressed
    delay(10);  //increase delay for more "sensitive" button, decrease for less sensitivity
    strat ++;
    if (strat > 8){
      strat = 0;
    }
  }
  switch (strat){
  case 0:
    //strat 1
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
    FastLED.show();
    break;
  
  case 1:
    //strat 2
    leds[0] = CRGB::Blue;
    leds[1] = CRGB::Blue;
    FastLED.show();
    break;

  case 2:
    //strat 2
    leds[0] = CRGB::Green;
    leds[1] = CRGB::Green;
    FastLED.show();
    break; 
  
  case 3:
    //strat 2
    leds[0] = CRGB::Yellow;
    leds[1] = CRGB::Yellow;
    FastLED.show();
    break;
  }
}

