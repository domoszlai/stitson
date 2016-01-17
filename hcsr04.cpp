#include <mthread.h>
#include "hcsr04.h"
#include "robotcar.h"

HCSR04* sonarAdapter;

HCSR04::HCSR04(int triggerPin, int echoPin)
{
    sonarAdapter = this;

    lastMeasure = MAX_CM_DISTANCE;
    lastMeasureTime = 0;
    nrReadings = 0;

    for(int i=0; i<5; i++)
    {
      lastReadings[i] = MAX_CM_DISTANCE;
    }

    #ifdef ENABLE_SONAR
    sonar = new NewPing(triggerPin, echoPin, MAX_CM_DISTANCE);
    #else
    sonar = NULL;
    #endif
}

void globalEchoCheck()
{
   sonarAdapter->echoCheck();
}

void HCSR04::echoCheck() 
{
    if (sonar->check_timer()) {
    
        lastReadings[nrReadings++ % 5] = sonar->ping_result / US_ROUNDTRIP_CM;
        
        lastMeasure = median(
                  lastReadings[0], 
                  lastReadings[1],
                  lastReadings[2],
                  lastReadings[3],
                  lastReadings[4]);
               
        #ifdef DEBUG
/*        Serial.print("HCSR04 lastReading: ");
        Serial.println(sonar->ping_result / US_ROUNDTRIP_CM);
        Serial.print("HCSR04 lastReadings: ");
        Serial.print(lastReadings[0]);
        Serial.print(", ");
        Serial.print(lastReadings[1]);
        Serial.print(", ");
        Serial.print(lastReadings[2]);
        Serial.print(", ");
        Serial.print(lastReadings[3]);
        Serial.print(", ");
        Serial.println(lastReadings[4]);*/
        Serial.print("HCSR04 median: ");
        Serial.println(this->lastMeasure);
        #endif        
    }
}

// Trick using XOR to swap two variables
#define swap(a,b) a ^= b; b ^= a; a ^= b;
#define sort(a,b) if(a>b){ swap(a,b); }

// http://cs.engr.uky.edu/~lewis/essays/algorithms/sortnets/sort-net.html
int HCSR04::median(int a, int b, int c, int d, int e)
{
    sort(a,b);
    sort(d,e);  
    sort(a,c);
    sort(b,c);
    sort(a,d);  
    sort(c,d);
    sort(b,e);
    sort(b,c);
    // this last one is obviously unnecessary for the median
    //sort(d,e);
  
    return c;
}

long HCSR04::measure()
{
    return lastMeasure;
}

bool HCSR04::loop()
{
    if(sonar == NULL) return false;
  
    if (millis() >= lastMeasureTime + PING_INTERVAL) 
    {
        lastMeasureTime = millis();
        sonar->ping_timer(globalEchoCheck);
    }

    return true;
}


