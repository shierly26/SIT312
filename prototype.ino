//
//    usage.h
//    Purpose: Demonstration of how to use the HC-SR04 driver
//
//    Author: Richard Nash
//    Version: 1.0.1

#include "HC-SR04.h"
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

/*
 The HC-SR04 device is a 5V device. So, VIN (which is 5V when connected to a USB power supply)
 is used to power it. Also, the "Echo" pin will present a 5V pulse, which can be connected
 to any of the D* GPIO pins, as they are 5V tolerant. However, they cannot be connected to
 non-5V tolerant pins, like the A* pins, even if in digitial mode.

 This example expects the wiring to be as follows:
    Photon  HC-SR04
    GND     GND
    VIN     VCC
    A0      Trig
    D0      Echo
*/
// sensor1(front) = A0;
// sensor2(left) = A1;
// sensor3(right) = A2;
// sensor4(back) = A3;




// trigger =output / echo pins=input
const int triggerPin_front = A0;
const int triggerPin_left = A1;
const int triggerPin_right = A2;
const int triggerPin_back = A3;

const int echoPin_front = D0;
const int echoPin_left = D1;
const int echoPin_right = D2;
const int echoPin_back = D3;

HC_SR04 rangefinder_front = HC_SR04(triggerPin_front, echoPin_front);
HC_SR04 rangefinder_left = HC_SR04(triggerPin_left, echoPin_left);
HC_SR04 rangefinder_right = HC_SR04(triggerPin_right, echoPin_right);
HC_SR04 rangefinder_back = HC_SR04(triggerPin_back, echoPin_back);




void setup()
{
    // Read sensor
    Serial.begin(9600
    Serial1.begin(9600);
    
    rangefinder_front.init();
    rangefinder_left.init();
    rangefinder_right.init();
    rangefinder_back.init();s
    
    execute_CMD(0x3F, 0, 0); // Send request for initialization parameters
    while (Serial1.available()<10) // Wait until initialization parameters are received (10 bytes)
    delay(30); // Pretty long delays between succesive commands needed (not always the same)
    // Initialize sound to very low volume. Adapt according used speaker and wanted volume
    execute_CMD(0x06, 0, 5); // Set the volume (0x00~0x30)
    
}
void loop()
{
    float cm_front = rangefinder_front.distCM();
    float cm_left = rangefinder_left.distCM();
    float cm_right = rangefinder_right.distCM();
    float cm_back = rangefinder_back.distCM();
    
    
   
    if(cm_front < 25 && cm_front > 0)
    {
        
        Particle.publish("Front",String(cm_front), PRIVATE);
        play();
    }
    
    if(cm_left < 25 && cm_left > 0)
    {
        //if(cm_frontright < 25)
        {
            Particle.publish("Left", String(cm_left), PRIVATE);
            play();
        }
        
    }
    if(cm_right < 25 && cm_right > 0)
    {
        
        Particle.publish("right",String(cm_right) , PRIVATE);
        play();
            
    }
    if(cm_back < 25 && cm_back> 0)
    {

        Particle.publish("back", String(cm_back),PRIVATE);
        play();
    }
    delay(1500);
    
}

void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}

void execute_CMD(byte CMD, byte Par1, byte Par2) // Excecute the command and parameters
{
 // Calculate the checksum (2 bytes)
 int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

 // Build the command line
 byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte};

 //Send the command line to the module
 for (byte k=0; k<10; k++)
 {
  Serial1.write( Command_line[k]);
 }
}
