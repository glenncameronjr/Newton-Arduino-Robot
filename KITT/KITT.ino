//KITT lights program
int d = 200;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop()
{
  digitalWrite(2,HIGH); //turn on LED 
  delay(d);  //wait half a second
  digitalWrite(2, LOW); //turn off LED
    
  digitalWrite(3,HIGH);
  delay(d);
  digitalWrite(3, LOW);
  
  digitalWrite(4,HIGH);
  delay(d);
  digitalWrite(4, LOW);
  
  digitalWrite(5,HIGH);
  delay(d);
  digitalWrite(5, LOW);
  
  digitalWrite(6,HIGH);
  delay(d);
  digitalWrite(6, LOW);
  
  digitalWrite(5,HIGH);
  delay(d);
  digitalWrite(5, LOW);
  
  digitalWrite(4,HIGH);
  delay(d);
  digitalWrite(4, LOW);
  
  digitalWrite(3,HIGH);
  delay(d);
  digitalWrite(3, LOW);

}

