/*************************************************************************
* File Name          : TestMotorDriver.ino
* Author             : Steve
* Updated            : Jasen
* Version            : V1.0.1
* Date               : 11/14/2013
* Description        : Test for Makeblock Electronic modules of Me -Motor 
                       Driver. You can directly connect a motor to M1 or M2 Port, or connect to PORT_1 or PORT_2 through a DC                        motor driver
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor motor3(M1);
MeDCMotor motor4(M2);

uint8_t motorSpeed = 255;

MeUltrasonicSensor ultraSensor(PORT_3);

void setup()
{

}
void loop()
{
   while (ultraSensor.distanceCm() > 10) {
        motor3.run(motorSpeed);
	motor4.run(motorSpeed);
   }
   
   //tried turing left but changes to right if stuck
   int x = 0;
   int i =0;
   if (ultraSensor.distanceCm() < 10) {
     
     while (x <= 5 && ultraSensor.distanceCm() < 10) {
       motor3.stop();
       motor4.stop();
       motor3.run(motorSpeed);
       
       delay(2000);
       motor3.stop();
       x++;
     
     }  
     while (x > 5 && i <= 5 && ultraSensor.distanceCm() < 10) {
         motor4.run(motorSpeed);
         delay(2000);
         motor4.stop();
         i++;
       }
     if (x >5 && i>5 && ultraSensor.distanceCm() < 10) {
         motor3.run(-motorSpeed);
	 motor4.run(-motorSpeed);
          delay(2000);
     }
    
   }
   
   
/*
	delay(2000);
   
        motor3.stop();
	motor4.stop();
	delay(100);

	
        motor3.run(-motorSpeed);
        motor4.run(-motorSpeed);
	delay(2000);
	
        motor3.stop();
	motor4.stop();
	delay(2000);

  */
  
}

