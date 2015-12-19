#include <mthread.h>
#include "hcsr04.h"
#include "robotcar.h"

#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

HCSR04* sonarAdapter;

HCSR04::HCSR04(int triggerPin, int echoPin)
{
    sonarAdapter = this;

    #ifdef ENABLE_SONAR
    this->sonar = new NewPing(triggerPin, echoPin, 200);
    this->lastMeasure = MAX_DISTANCE;
    this->lastMeasureTime = 0;
    #else
    this->sonar = NULL;
    #endif
}

void globalEchoCheck()
{
   sonarAdapter->echoCheck();
}

void HCSR04::echoCheck() 
{
    if (this->sonar->check_timer()) {
        this->lastMeasure = this->sonar->ping_result / US_ROUNDTRIP_CM;

        #ifdef DEBUG
        Serial.print("HCSR04: ");
        Serial.println(this->lastMeasure);
        #endif        
    }
}

long HCSR04::measure()
{
    if(this->sonar == NULL)
    {
        return MAX_DISTANCE;
    }
    else
    {        
        return this->lastMeasure;
    }    
}

bool HCSR04::loop()
{
    if(this->sonar == NULL) return false;
  
    if (millis() >= this->lastMeasureTime + PING_INTERVAL) 
    {
        this->lastMeasureTime = millis();
        this->sonar->ping_timer(globalEchoCheck);
    }

    return true;
}


