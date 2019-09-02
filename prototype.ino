//
//    usage.h
//    Purpose: Demonstration of how to use the HC-SR04 driver
//
//    Author: Richard Nash
//    Version: 1.0.1

#include "HC-SR04.h"

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
// sensor1(left) = A0;
// sensor2(front left) = A1;
// sensor3(front right) = A2;
// sensor4(right) = A3;


// trigger / echo pins
const int triggerPin_left = A0;
const int triggerPin_frontleft = A1;
const int triggerPin_frontright = A2;
const int triggerPin_right = A3;

const int echoPin_left = D0;
const int echoPin_frontleft = D1;
const int echoPin_frontright = D2;
const int echoPin_right = D3;

//HC_SR04 rangefinder_left = HC_SR04(triggerPin_left, echoPin_left);
//HC_SR04 rangefinder_frontleft = HC_SR04(triggerPin_frontleft, echoPin_frontleft);
HC_SR04 rangefinder_frontright = HC_SR04(triggerPin_frontright, echoPin_frontright);
//HC_SR04 rangefinder_right = HC_SR04(triggerPin_right, echoPin_right);

void setup()
{
    Serial.begin(9600);
    //rangefinder_left.init();
    //rangefinder_frontleft.init();
    rangefinder_frontright.init();
    //rangefinder_right.init();

}


void loop()
{
    //float cm_left = rangefinder_left.distCM();
  //  float cm_frontleft = rangefinder_frontleft.distCM();
    float cm_frontright = rangefinder_frontright.distCM();
    //float cm_right = rangefinder_right.distCM();
    
   /* 
    if(cm_left < 25)
    {
        Particle.publish("Distance in left:", String(cm_left));  
       
    }
    if(cm_frontleft < 25)
    {
        //if(cm_frontright < 25)
        {
            Particle.publish("Distance in frontleft:", String(cm_frontleft)); 
            
            
        }
        
    }
    */
    if(cm_frontright < 25)
    {
        
        Particle.publish("Distance in frontright:", String(cm_frontright)); 
    }
    /*
    if(cm_right < 25)
    {
        Particle.publish("Distance in right:", String(cm_right));
        
    }
  */
    delay(1500);
}

