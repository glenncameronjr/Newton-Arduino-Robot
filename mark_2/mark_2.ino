/*************************************************************************
* File Name          : TestServoDriver.ino
* Author             : Glenn Cameron
* Updated            : 2/22/1015
* Version            : V2.0.1
* Date               : 2/23/2015
* Description        :  
                        
* License            : CC-BY-SA 3.0
* Copyright (C) 2015 Cameron Robotics Inc. All right reserved.
* http://www.glenncameronjr.com
**************************************************************************/
///needs a reverse if it is stuck on the right and left but not middle

#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h> //include the Servo library;

MePort port(PORT_2);
MeUltrasonicSensor ultraSensor(PORT_3); //Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield.
MeDCMotor motor3(M1);
MeDCMotor motor4(M2);

Servo servoDriver1;  // create servo object to control a servo 
int servo1pin =  port.pin2();//attaches the servo on PORT_1 SLOT2 to the servo object

int right = 150;
int center = 95;
int left = 30;
int blockageCenter = 0;
int blockageRight = 0;
int blockageLeft = 0;

//distance to check for objects in cm
int distanceObject = 20;

uint8_t motorSpeed = 255;


void setup()
{
  servoDriver1.attach(servo1pin);  // attaches the servo on servopin1
  Serial.begin(9600); 
}

void loop()
{
  moveRobot();
  //moveHead();      
}


