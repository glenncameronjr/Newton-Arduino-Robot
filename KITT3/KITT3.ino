int d = 15;

void setup()
{
  pinMode(3, OUTPUT);
  
  pinMode(6, OUTPUT);
  
}


void loop()
{
  
  for (int a = 0; a < 256 ; a++) 
  {
   analogWrite(3, a);
   analogWrite(6, a);
   delay(d); 
  }
  
  for (int a = 255; a < 256 ; a--)
  {
   analogWrite(3, a);
   analogWrite(6, a);
   delay(d);   
  }  
}
