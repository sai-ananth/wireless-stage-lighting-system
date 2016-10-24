# wireless-stage-lighting-system
Saral Anubhradjathe

 
Abstract- Power consumption is a major factor that has to be controlled in today’s world. In this paper we propose wireless communication to monitor the amount of power that is being used and to manually control it. This proposal integrates Arduino based microcontroller ATmega-328 and RF 12 communication protocol. This module is easily applicable in the practical world. It can be used in industries and workplaces (offices) to reduce the power consumption efficiently.

Introduction:  The Arduino UNO board has analog and digital pins. The potentiometers connected to the analog pins(inputs) are also pins of the IC of the microcontroller ATMega-328 . As the input analog signals are varied, RF signals are sent and received at the other end. The received analog signals control the power  of any voltage controlled device, here we are considering LEDs.

The transmission and reception of the data done using the RF communication protocol on RF 12 Module.
Operation-RF 12 communication:
 The analog  inputs  to the RF module are given through the analog pins of Arduino board. The analog readings range from 0 to 1023, which are mapped onto a range of 0 to 255. 
Arduino works on a voltage supply of 5V whereas the RF 12 module works only at a voltage of 3.3V.  Hence, there is a requirement for a bridging circuit between the Arduino board and  
the RF 12 module which steps down the voltage from 5V to 3.3V. Here we are using resistors connected in the combination as shown in the block diagram for stepping down the voltage to 3.3V.
Each RF module is given a node ID which is unique and a network group to work within. While sending the data packet, the RF module also sends it’s node ID and ‘CRC’ (cyclic redundancy check) bit. The cyclic redundancy check is then performed to check for errors in the data by adding a byte.
When the receiver receives the data packet, it checks the ID of the node from which it is receiving. Then the Arduino board runs the CRC on the  received data again. The data is unfolded from the data packets and given to the PWM (pulse width modulation) pins on the Arduino board which are given to LED. This small scale project can be developed on a large scale which has many applications

Applications: 
1.It  can be used for reducing the power consumption in industries, homes, hospitals etc.
2. It can be used in musical instruments like electronic tanpura, electronic tabla.
3. A Quadcopter can be controlled with this.
4. This  technology can also be used to control the speed of motors.

Conclusion: The project functions in such a way that the power consumption is reduced and can be used in any field. 




 


