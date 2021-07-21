#include <Mouse.h>
const int ledPin = 13;
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
 
void loop() 
{
  digitalWrite(ledPin, HIGH);   // set the LED on
  if(Serial.available())
  {
    int data = Serial.read();
    if(data == 'A')
      Mouse.click();
  }
}