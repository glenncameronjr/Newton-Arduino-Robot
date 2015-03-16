//2 directional traffic lights

//define pins that buttons and lights connect to

#define westButton 3
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define yellowBlinkTime 500 // 0.5 seconds for yellow light blink

boolean trafficWest = true; //west = true, east = false
int flowTime = 10000; //amount of time to let traffic flow
int changeDelay = 2000; //amount of time between color changes

void setup()
{
  //setup digital I/O pins
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  
  //set initial state for lights - west side is green first
  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);  
}

void loop()
{
 if ( digitalRead(westButton) == HIGH ) //request west>east traffic flow 
  {
    if ( trafficWest != true)
    //only continue if taffic flowing in the opposite (east) direction
    {
     trafficWest = true;
    delay(flowTime);
    digitalWrite(eastGreen, LOW);
    digitalWrite(eastYellow, HIGH);
    delay(changeDelay);
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, HIGH);  
    delay(changeDelay);
    for ( int a = 0; a < 5; a++) 
         {
           digitalWrite(westYellow, LOW);
           delay(yellowBlinkTime);
           digitalWrite(westYellow, HIGH);
           delay(yellowBlinkTime);             
    }    
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, LOW);
    digitalWrite(westGreen, HIGH);
   }
 }
if ( digitalRead(eastButton) == HIGH)
{
  if (trafficWest == true)
  {
   trafficWest = false;
  delay(flowTime);
  digitalWrite(westGreen, LOW);
  digitalWrite(westYellow, HIGH);
  delay(changeDelay);
  digitalWrite(westYellow, LOW);
  digitalWrite(westRed, HIGH);
  delay(changeDelay);
  for ( int a = 0; a < 5; a++)
  {
      digitalWrite(eastYellow, LOW);
      delay(yellowBlinkTime);
      digitalWrite(eastYellow, HIGH);
      delay(yellowBlinkTime);  
  }
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastRed, LOW);
  digitalWrite(eastGreen, HIGH);
  } 
  }

}