/*************************************************************************
* File Name          : Newton.ino
* Author             : Glenn
* Updated            : Cameron
* Version            : V1.0.1
* Date               : 1/20/2015
* Description        : Makes the newton bot autonomous by avoiding objects using sonar
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//check port connection
MeUltrasonicSensor ultraSensor(PORT_3);

MeDCMotor motorR(M1);
MeDCMotor motorL(M2);

uint8_t motorSpeed = 255;

void setup()
{

}
//add in remote override if a digital switch is turned on... Need to find switch plugin
void loop()
{
  //while nothing is in the way move forward
  int r = 0;
  int  l = 0;
  
  while (ultraSensor.distanceCm() >=10) {
    motorR.run(motorSpeed);
    motorL.run(motorSpeed);
  }
    //is something is in the way turn right
  while (ultraSensor.distanceCm() < 10) {
    if(ultraSensor.distanceCm() < 10 && r==0 && l==0) {
          stopMove();
          delay(2000);
          moveRight();
          r++; 
            //turn left if you are still stuck
           else if(ultraSensor.distanceCm() < 10 && r==1 && l==0) {
              stopMove();
              moveLeft();
              delay(2000);
              l++;
            }
             //if something is in the way after reversing and after moving right and left move backward
           else if(ultraSensor.distanceCm() < 10 && r==1 && l==1) {
              stopMove();
              moveBack();
              delay(2000);
              //then turn right (change to a random side by using a random 0 or 1)
              stopMove();
              moveRight();
              delay(2000);       
              }
    } 
        //buzzes while moving in order to know where in the while loop we are  
            else {
               buzzerOn();
              delay(1000);
              buzzerOff();
              delay(1000);
              
               digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
               delay(1000);              // wait for a second
               digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
               delay(1000);              // wait for a second
            }
           }
   }


void moveRight() {
  motorL.run(motorSpeed);
  delay(1000); 
}

void moveLeft() {
   motorR.run(motorSpeed);
   delay(1000);   
}

void moveBack() {
   motorR.run(-motorSpeed);
   motorL.run(-motorSpeed); 
   delay(3000);
}

void stopMove() {
  motorR.stop();
  motorL.stop();
}


