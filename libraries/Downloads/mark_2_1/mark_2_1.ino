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
int distanceObject = 28;

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

//center the sonar 
int centerSonar(){
  //goes center and checks to see whether something is in the way
  //if not then it returns a value that is passed forwar
  servoDriver1.write(center); //centers the servo
  delay(1000);
  
    if (ultraSensor.distanceCm() < distanceObject) 
     {
         buzzerOn();
         delay(1000);
         buzzerOff();
         delay(1000);
         blockageCenter = 1; //1 means an object is in front
         Serial.print("Distance : ");
         Serial.print(ultraSensor.distanceCm());
         Serial.println(" cm");
         Serial.print("BLOCKAGE CENTER  : ");
         Serial.println(blockageCenter);
         return blockageCenter;
     }
    else 
    {
      return blockageCenter = 0;  //0 means move forward
    }
   delay(2000);  // Wait for the servo rotation to the set position[
}

int rightSonar(){
  //goes center and checks to see whether something is in the way
  //if not then it returns a value that is passed forwar
  servoDriver1.write(right); //centers the servo
  delay(1000);  
   if (ultraSensor.distanceCm() < distanceObject) 
        {
             buzzerOn();
             delay(1000);
             buzzerOff();
             delay(1000);
             blockageRight = 1; //1 means an object is on the right
             Serial.print("Distance : ");
             Serial.print(ultraSensor.distanceCm());
             Serial.println(" cm");
             Serial.print("BLOCKAGE RIGHT  : ");
             Serial.println(blockageRight);
             return blockageRight;
        }
    else 
    {
      return blockageRight = 0;  //0 means move forward
    }
   delay(2000);  // Wait for the servo rotation to the set position[
}

int leftSonar(){
  //goes center and checks to see whether something is in the way
  //if not then it returns a value that is passed forwar
  servoDriver1.write(left); //centers the servo
  delay(1000);
   if (ultraSensor.distanceCm() < distanceObject) 
        {
             buzzerOn();
             delay(1000);
             buzzerOff();
             delay(1000);
             blockageLeft = 1; //1 means an object is on the left
             Serial.print("Distance : ");
             Serial.print(ultraSensor.distanceCm());
             Serial.println(" cm");
             Serial.print("BLOCKAGE LEFT  : ");
             Serial.println(blockageLeft);
             return blockageLeft;
        }
    else 
    {
      return blockageLeft = 0;  //0 means nothing is in the way
    }
   delay(2000);  // Wait for the servo rotation to the set position[
}

int moveHead()
{
  centerSonar();
  //returns 1 0r 0
  rightSonar();
  //returns 2 or 0
  servoDriver1.write(center);
  delay(1000);
  leftSonar();
  //returns 1 or 0
  servoDriver1.write(center);
  
  Serial.println("Blockage results returned: ");
  Serial.println(blockageCenter);
  Serial.println(blockageRight);
  Serial.println(blockageLeft);
  
 
  if (blockageCenter == 1)
    {
     // turn left
    if( blockageRight == 1 && blockageLeft == 0) {
       motor3.run(motorSpeed);
       delay(1500);
       motor3.stop();
    }
    //turn right
    else if(blockageLeft == 1 && blockageRight ==0) {
       motor4.run(motorSpeed);
       delay(1500);
       motor3.stop();
    }
    //reverse
    else if (blockageLeft == 1 && blockageRight ==1)   {
       motor3.run(-motorSpeed);
       motor4.run(-motorSpeed);
       delay(2500);
       motor3.stop();
       motor4.stop();
       //moveHead();
    } 
    //If no blockage go forward by starting loop all over again
    else {
      blockageCenter = 0;
      
      /*
      motor3.run(motorSpeed);
      motor4.run(motorSpeed);
      delay(3000);
      motor3.stop();
      motor4.stop();
      */
      
    }   
  } 
}


void moveRobot(){
 //this kind of works with the distance object is 30 and the others are shorter. IE remove dsitance object and use 30.
  while (ultraSensor.distanceCm() >= distanceObject) {
        motor3.run(motorSpeed);
		motor4.run(motorSpeed);
        //delay (500);//testing to see if this solves the running into things problem
   }
   
   if (ultraSensor.distanceCm() < distanceObject) {
     motor3.stop();
     motor4.stop();
     moveHead();  
   } 
}



//lets make a 0 nothing is in the way and a 1 means something is in the way
  

