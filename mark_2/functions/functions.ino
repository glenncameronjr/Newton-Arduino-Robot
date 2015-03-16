void moveRobot(){
 //this kind of works with the distance object is 30 and the others are shorter. IE remove dsitance object and use 30.
  while (ultraSensor.distanceCm() > 0) {
          
      if (ultraSensor.distanceCm() >= distanceObject - 9) {
        motor3.run(motorSpeed);
        motor4.run(motorSpeed);
        blockageCenter = 0;
      }
   
      else if (ultraSensor.distanceCm() < distanceObject - 9) {
       motor3.stop();
       motor4.stop();
       blockageCenter = 1;
       moveHead();  
      } 
      
      else {
        buzzerOn();
        
        buzzerOff();
        
      }
  }
}


int moveHead()
{
  
  //set up a counter loop here so if it runs through more than once something happens
  centerSonar(); //returns 1 0r 0
  
  rightSonar(); //returns 1 or 0
  
  //centers sonar to look more life like...
  servoDriver1.write(center);
  delay(1000);
  
  leftSonar(); //returns 1 or 0
  
  servoDriver1.write(center);
  
  
 
  if (blockageCenter == 1)
    {
     // turn left
    if( blockageLeft == 0 &&  blockageRight == 1) {
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
       delay(2000);
       motor3.stop();
       motor4.stop();
       //moveHead();
    } 
    
    else if (ultraSensor.distanceCm() >= distanceObject - 10) {
        motor3.run(motorSpeed);
        motor4.run(motorSpeed);
      }
    //If no blockage go forward by starting loop all over again 
    else {
      //blockage center was already set
      motor3.run(-motorSpeed);
      motor4.run(-motorSpeed);
      delay(750);
      motor3.stop();
      motor4.stop();
      blockageCenter = 0;
      moveRobot();
      
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


//center the sonar 
int centerSonar(){
  //goes center and checks to see whether something is in the way
  //if not then it returns a value that is passed forwar
  servoDriver1.write(center); //centers the servo
  delay(1000);
  
    if (ultraSensor.distanceCm() < distanceObject + 5) 
     {
         buzzerOn();
         delay(1000);
         buzzerOff();
         delay(1000);
         //checking to see if this is the reason for the endless movehead loop
         //blockageCenter = 1; //1 means an object is in front
         return blockageCenter;
     }
    else 
    {
     // return blockageCenter = 0;  //0 means move forward
    }
   delay(2000);  // Wait for the servo rotation to the set position[
}

int rightSonar(){
  //goes center and checks to see whether something is in the way
  //if not then it returns a value that is passed forwar
  servoDriver1.write(right); //centers the servo
  delay(1000);  
   if (ultraSensor.distanceCm() < distanceObject + 5) 
        {
             buzzerOn();
             delay(1000);
             buzzerOff();
             delay(1000);
             blockageRight = 1; //1 means an object is on the right
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
   if (ultraSensor.distanceCm() <= distanceObject + 5) 
        {
             buzzerOn();
             delay(1000);
             buzzerOff();
             delay(1000);
             blockageLeft = 1; //1 means an object is on the left
             return blockageLeft;
        }
    else 
    {
      return blockageLeft = 0;  //0 means nothing is in the way
    }
   delay(2000);  // Wait for the servo rotation to the set position[
}

  

