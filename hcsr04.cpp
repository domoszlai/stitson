#include <mthread.h>
#include "hcsr04.h"
#include "robotcar.h"

HCSR04::HCSR04(int triggerPin, int echoPin)
{
    //this->sonar = new NewPing(triggerPin, echoPin, 200);
    //this->lastMeasureTime = -200;
}

long HCSR04::measure()
{
    if(this->sonar == NULL) return 1000; // NICE big number

    if(millis() - this->lastMeasureTime < 50) return this->lastMeasure;
  
    int result = this->sonar->ping();
    result = this->sonar->convert_cm(result);
    
    if(result > 0 && abs(this->lastMeasure - result) > 20)
    {
      #ifdef DEBUG
      Serial.println("HCSR04 FLIP");
      #endif
      
      result = this->sonar->ping_median(10);
      result = this->sonar->convert_cm(result);      
    }
    
    this->lastMeasure = result == 0 ? 200 /* far away */ : result;
    this->lastMeasureTime = millis();
    
    #ifdef DEBUG
    Serial.print("HCSR04: ");
    Serial.println(lastMeasure);
    #endif
    
    return this->lastMeasure;
}

