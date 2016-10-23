/*
 * sending Analog data with the help rf12 module.
 * 
 * It collects the analog sensor data and converts to a form suitable pwm pin and transmits  the
 * data in the form of packets to reciver.
 * 
 * connect the center terminals of the POTs to the analog pins and one terminal to 5v and the other to ground
 * 
 * Arduino works on both 5v and 3.3v but the rf12 module only  works on 3.3v . So the  
 * connections going from arduino to rf12 must be stepped down to 3.3v and the connections 
 * going from rf12 to arduino can be connected directly.
 * 
 * rf12 pin configuuration
 * SDI - DIGITAL 11
 * N SEL - DIGITAL 10
 * N IRQ - DIGITAL 2
 * SCK - DIGITAL 13
 * SDO - DIGITAL 12
 * 
 * Inputs :
 * A0 - POT1 CENTER PIN
 * A1 - POT2 CENTER PIN
 * A2 - POT3 CENTER PIN
 * A3 - POT4 CENTER PIN
 * A4 - POT5 CENTER PIN
 * A5 - POT6 CENTER PIN
*/

#include <JeeLib.h>

Port leds (1);                                       //to use the Tx and Rx led 
MilliTimer sendTimer;                                //timer for sending the data
int sensor1=A0;                                      //initilizing 6 sensors(POT) to the analog pins A0 to A5 respectively
int sensor2=A1;
int sensor3=A2;
int sensor4=A3;
int sensor5=A4;
int sensor6=A5;
typedef struct{int a0,a1,a2,a3,a4,a5;}              //analog valuess to be sent
payloadtx;                                          //name of the structure
payloadtx emont;                                    //instance of the structure(payloadtx)
byte needToSend;                                    //this helps us to enable the rf12 module to send the signal
int node_id=10;                                     //sets the node id of the rf12 module to 10
const int networkgroup=33;                          //sets the network group of the rf12 module to 33
String rf_freq="RF12_868MHZ";                       //sets the frequency of the rf12 module communication to 868MHZ

static void sendLed (byte on) {                     //to make the tx led high or low while sending the data
    leds.mode(OUTPUT);                              
    leds.digiWrite(on);
}

void setup () {
    Serial.begin(57600);
    Serial.println(57600);
    Serial.println("Send");
    rf12_initialize(node_id,rf_freq, networkgroup);          //initializing the rf 12 module with its node id and its network group
}

void loop () {
    if (rf12_recvDone() && rf12_crc == 0) 
    {     
     // must be present for rf12_canSend() to work
    }
    
    if (sendTimer.poll(3000))                    //sends true every 3000 milli seconds
        needToSend = 1;                          //sends data every 3 seconds

    if (needToSend && rf12_canSend()) {
        needToSend = 0;                         // resets needToSend to 0 for the rf12 module to again wait for 3 seconds
        emont.a0=map(analogRead(sensor1), 0, 1023, 0, 255);         //updating the members of the instance(emont)of type structure(payloadtx)
        emont.a1=map(analogRead(sensor2), 0, 1023, 0, 255);
        emont.a2=map(analogRead(sensor3), 0, 1023, 0, 255);
        emont.a3=map(analogRead(sensor4), 0, 1023, 0, 255);
        emont.a4=map(analogRead(sensor5), 0, 1023, 0, 255);
        emont.a5=map(analogRead(sensor6), 0, 1023, 0, 255);
        sendLed(1);
        rf12_sendStart(0, &emont, sizeof emont);//sending the data
        delay(100);                            // otherwise led blinking isn't visible
        sendLed(0);
    }
}
