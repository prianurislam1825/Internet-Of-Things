#include<SoftwareSerial.h>

int sensorPin = A0; //pin yg di gunakan

int sensorValue = 0;

int led = 2; // pin led yg di gunakan

int buzzer = 4; // pin buzzer

void setup(){
  
   Serial.begin(9600);
   pinMode(led, OUTPUT);
   pinMode(buzzer, OUTPUT);
  
  
  }

void loop()
{
  Serial.println("pembacaan sensor api");

  sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);

  if (sensorValue < 100)
  {
    Serial.println(" ada api");
    digitalWrite(led,HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    
    }
  digitalWrite(led,LOW);
  digitalWrite(buzzer, LOW);
  delay(sensorValue);
  
  }
