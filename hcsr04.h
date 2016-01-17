#ifndef HCSR04_H
#define HCSR04_H

#define MAX_CM_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

#include <NewPing.h>

class HCSR04 : public Thread
{
public:
    HCSR04(int triggerPin, int echoPin);
        
    long measure();

    void echoCheck();
    
protected:
    bool loop();
private:
    NewPing* sonar;

    int lastReadings[5];
    int nrReadings;
    
    long lastMeasureTime;
    int lastMeasure;

    int median(int a, int b, int c, int d, int e);
};

#endif  // HCSR04_H
