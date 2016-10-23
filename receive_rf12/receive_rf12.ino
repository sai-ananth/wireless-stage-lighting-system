/*
 * sending Analog data with the help rf12 module.
 * 
 * It receives the sensor data in the form suitable for pwm pins.
 * 
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
 * Outputs :
 * 
*/

#include <JeeLib.h>
#define rf_freq RF12_433MHZ                       //sets the frequency of the rf12 module communication to 868MHZ
#define DATAFLASH 0

typedef struct{int a0,a1,a2,a3,a4,a5;}    //analog valuess to be sent
payloadtx;                 //name of the structure
payloadtx emont;             //instance of the structure(payloadtx)
Port leds (1);//to use the Tx and Rx led 
MilliTimer sendTimer;//timer for sending the data
byte needToSend; //this helps us to enable the rf12 module to send the signal
int node_id=20;                                     //sets the node id of the rf12 module to 20
const int networkgroup=159;                          //sets the network group of the rf12 module to 210



int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
static void receiveLed (byte on) {                     //to make the Rx led high or low while receiving the data
    leds.mode2(OUTPUT);
    leds.digiWrite2(!on);                             // inverse, because LED is tied to VCC
}

void setup () {
    Serial.begin(57600);
    Serial.println(57600);
    Serial.println("Receive");
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);


    rf12_initialize(node_id,rf_freq, networkgroup);  //initializing the rf 12 module with its node id and its network group
}
void loop () {
 //Serial.println(rf12_crc);
    if (rf12_recvDone() && rf12_crc == 0) {    //check for error
      Serial.println("receiving start");
      Serial.println(rf12_crc);
      Serial.println(rf12_hdr);
      
        receiveLed(1);                               
        int node=(rf12_hdr & 0x1F);             //getting the node id of the transmitting module
        Serial.println(node);  
        if(node==9)                           //checking if the transmitting module node id is 10
        {
        Serial.print("node: ");
        Serial.println(node);                  //printing the node id of the transmitting module 
        emont=*(payloadtx*)rf12_data;          //getting the transmitted data from the rf12 module
        analogWrite(led1,emont.a0);
        Serial.print("a0=");                   //printing the data from the instance(emont of the structure(payloadtx)
        Serial.println(emont.a0);
        analogWrite(led2,emont.a1);
        Serial.print("a1=");
        Serial.println(emont.a1);
        analogWrite(led3, emont.a2);
        Serial.print("a2=");
        Serial.println(emont.a2);
        analogWrite(led4,emont.a3);
        Serial.print("a3=");
        Serial.println(emont.a3);
        Serial.print("a4=");
        Serial.println(emont.a4);
        Serial.print("a5=");
        Serial.println(emont.a5);
        delay(100);        
        }
        Serial.println();
        delay(100); // otherwise led blinking isn't visible
        receiveLed(0);
     }
    
    if (sendTimer.poll(3000))   //sends true every 3000 milli seconds
        needToSend = 1;    //sends data every 3 seconds

    if (needToSend && rf12_canSend()) { 
      //must be present for rf12_recvDone() to work
        needToSend = 0;
       
    }
}
