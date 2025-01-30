# Tenn board 天
The tenn board is a PCB designed mainly for minisumo robots, but it can be used for other projects or categories.\
It's a simple to build mid-level PCB, uses mostly SMD components except for the switch and the processor.\
The processor is a Arduino Nano, which is widely avaiable, it has a option for using a 128x32 OLED screen but you can also hook up any other module that uses I2C.\
It uses DRV8871 as a motor controller, that has a peak current of 3.5A, and can support up to 50V, but we recommed not to surpass 6S (25.2V), the recommended range that we have tested and competed with is from 2S to 4S.\
## Features
- Dedicated Servo Pin with PWM control
- Dedicated Start Module pin
- Capability to connect up to 10 sensors (2 analog GPIO, 4 digital GPIO and 4 analog and digital GPIO)
- Voltage test pins
- Two programmable buttons
- XT30 connector
- On/Off switch
- M2 mounting holes for secure mounting
