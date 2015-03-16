void moveRobot(){
 //this kind of works with the distance object is 30 and the others are shorter. IE remove dsitance object and use 30.
  while (ultraSensor.distanceCm() > 0) {
      //try to check for the optimal way to go here in the future
      if (ultraSensor.distanceCm() >= distanceObject - 9) {
        motor3.run(motorSpeed);
        motor4.run(motorSpeed);
        blockageCenter = 0;
        stuck = 0; //#1
      }
   
      else if (ultraSensor.distanceCm() < distanceObject - 9) {
       motor3.stop();
       motor4.stop();
       blockageCenter = 1;
       stuck++; 
       moveHead(); 
      } 
      //else something is wrong;
      else {
        buzzerOn();        
        buzzerOff();
        stuck = 0;        
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
     //strange movement to get unstuck only 2 parts for the #2
     if (stuck >= 5) {
       motor3.run(motorSpeed);
       delay(1500);
       motor3.stop();
       motor4.run(motorSpeed);
       delay(1500);
       motor4.stop();
       motor3.run(-motorSpeed);
       motor4.run(-motorSpeed);
       delay(2000);
       motor3.stop();
       motor4.stop();
       moveRobot();
       
     }
     // turn left
     else if( blockageLeft == 0 &&  blockageRight == 1) {
       motor4.run(motorSpeed);
       delay(1250);
       motor4.stop();
       stuck++; 
    }
    
    //turn right if left is blocked
    else if(blockageLeft == 1 && blockageRight ==0) {
       motor3.run(motorSpeed);
       delay(1250);
       motor3.stop();
       stuck++; 
    }
    //reverse is right and left is blocked
    else if (blockageLeft == 1 && blockageRight ==1)   {
       motor3.run(-motorSpeed);
       motor4.run(-motorSpeed);
       delay(1000);
       motor3.stop();
       motor4.stop();
       stuck++; 
       
       //adding 0 to see if it stops the bot from reversing over and over again
       blockageLeft = 0;
       blockageRight = 0;
    } 
    //if distance in cnter is further than right and left go forward
    else if (distCenter >= distRight && distCenter >= distLeft){
        motor3.run(motorSpeed);
        motor4.run(motorSpeed);
        stuck++; 
    }
    
    //turn left if more distance is on left than right
    else if( distLeft > distCenter &&  distLeft > distRight) {
       motor4.run(motorSpeed);
       delay(1250);
       motor4.stop();
       stuck++; 
    }
    //turn right if more distance on right than left
    else if(distRight > distCenter && distRight > distCenter) {
       motor3.run(motorSpeed);
       delay(1250);
       motor3.stop();
       stuck++; 
    }
      
    //distance is large in front go forward
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
         blockageCenter = 1;
         return blockageCenter;
     }
    else 
    {
     // return blockageCenter = 0;  //0 means move forward
     distCenter = ultraSensor.distanceCm();
     return distCenter;
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
      distRight = ultraSensor.distanceCm();
      return distRight;
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
      distLeft = ultraSensor.distanceCm();
      return distLeft;
    }
   delay(2000);  // Wait for the servo rotation to the set position[
}
