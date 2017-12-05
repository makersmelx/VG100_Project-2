#include <Arduino.h>
int state_2 = 0;
int state_3 = 0;

void setup(){
  Serial.begin(57600);
  pinMode(31, INPUT);
  pinMode(30,INPUT);
}


void loop(){
    state_2 = digitalRead(31);
    state_3 =digitalRead(30);
    if(state_2 == HIGH)
    {
      Serial.println("11 been hit");
    }
    if(state_3 == HIGH)
    {
      Serial.println("10 been hit");
    }
    
}
