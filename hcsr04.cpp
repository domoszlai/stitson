#include "mthread.h"
#include "hcsr04.h"

HCSR04::HCSR04(int triggerPin, int echoPin)
{
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
    
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

long HCSR04::measure()
{
  long duration, distance;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  return distance;
}

