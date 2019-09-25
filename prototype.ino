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

const int buzzer = D4;

int cm_front;
int cm_left;
int cm_right;
int cm_back;
int front = 0;
int left = 0;
int right = 0;
int back = 0;

HC_SR04 rangefinder_front = HC_SR04(triggerPin_front, echoPin_front);
HC_SR04 rangefinder_left = HC_SR04(triggerPin_left, echoPin_left);
HC_SR04 rangefinder_right = HC_SR04(triggerPin_right, echoPin_right);
HC_SR04 rangefinder_back = HC_SR04(triggerPin_back, echoPin_back);




void setup()
{
    // Read sensor
    Serial.begin(9600);
    rangefinder_front.init();
    rangefinder_left.init();
    rangefinder_right.init();
    rangefinder_back.init();
    pinMode(buzzer, OUTPUT);
    
    Particle.variable("Front", front);
    Particle.variable("Left", left);
    Particle.variable("Right", right);
    Particle.variable("Back", back);
}
void loop()
{
    cm_front = rangefinder_front.distCM();
    front = cm_front;
    cm_left = rangefinder_left.distCM();
    left = cm_left;
    cm_right = rangefinder_right.distCM();
    right = cm_right;
    cm_back = rangefinder_back.distCM();
    back = cm_back;
    
    
   
    if(cm_front < 25 && cm_front > 0)
    {
        
        Particle.publish("Front","Object-Detected", PRIVATE);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
    }
    
    if(cm_left < 25 && cm_left > 0)
    {
        //if(cm_frontright < 25)
        {
            Particle.publish("Left", "Object-Detected", PRIVATE);
            digitalWrite(buzzer,HIGH);
            delay(300);
            digitalWrite(buzzer, LOW);
            delay(300);
            digitalWrite(buzzer,HIGH);
            delay(300);
            digitalWrite(buzzer, LOW);
            delay(300);
            digitalWrite(buzzer,HIGH);
            delay(300);
            digitalWrite(buzzer, LOW);
        }
        
    }
    if(cm_right < 25 && cm_right > 0)
    {
        
        Particle.publish("right","Object-Detected" , PRIVATE);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
            
    }
    if(cm_back < 25 && cm_back> 0)
    {

        Particle.publish("back", "Object-Detected",PRIVATE);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
        digitalWrite(buzzer,HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        
    }
    delay(1500);
    
}