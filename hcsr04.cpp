#include "mthread.h"
#include "hcsr04.h"

HCSR04::HCSR04(int triggerPin, int echoPin)
{
    //this->sonar = new NewPing(triggerPin, echoPin, 200);
    this->lastMeasureTime = -200;
}

long HCSR04::measure()
{
    if(this->sonar == NULL) return 1000; // NICE big number
  
    if(millis() - this->lastMeasureTime < 100) return this->lastMeasure;
  
    int result = this->sonar->ping_cm();
    this->lastMeasure = result == 0 ? 200 : result;
    this->lastMeasureTime = millis();
    
    return this->lastMeasure;
}

