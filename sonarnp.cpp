#include "sonarnp.h"
#include "robotcar.h"

SonarNP* SonarNP::instance = NULL;

SonarNP::SonarNP(int triggerPin, int echoPin)
{
    lastMeasure = MAX_CM_DISTANCE;
    
    if(instance == NULL)
    {
        instance = this;

        lastMeasureTime = 0;
        nrReadings = 0;

        // This makes the first measurements returning MAX_CM_DISTANCE 
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
    else
    {
        Serial.println("WARNING: HCSR04: Only one instance can be created");
    }
}

void SonarNP::globalEchoCheck()
{
    instance->echoCheck();
}

void SonarNP::echoCheck() 
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
        Serial.print("HCSR04 reading: ");
        Serial.print(lastReadings[(nrReadings - 1) % 5]);
        Serial.print(", median: ");
        Serial.println(lastMeasure);
        #endif        
    }
}

// Trick using XOR to swap two variables
#define swap(a,b) a ^= b; b ^= a; a ^= b;
#define sort(a,b) if(a>b){ swap(a,b); }

// http://cs.engr.uky.edu/~lewis/essays/algorithms/sortnets/sort-net.html
// Median could be computed two less steps...
int SonarNP::median(int a, int b, int c, int d, int e)
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

int SonarNP::measure()
{
    return lastMeasure;
}

bool SonarNP::loop()
{
    if(sonar == NULL) return false;
  
    if (millis() >= lastMeasureTime + PING_INTERVAL) 
    {
        lastMeasureTime = millis();
        sonar->ping_timer(globalEchoCheck);
    }

    return true;
}


