#ifndef SONARNP_H
#define SONARNP_H

#include <mthread.h>
#include <NewPing.h>

#define MAX_CM_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

/*
 * NewPing based non-blocking sonar readings with median noise filtering
 */
class SonarNP : public Thread
{
public:
    SonarNP(int triggerPin, int echoPin);     
    
    // Returns the last measurement   
    int measure();
protected:
    bool loop();
private:
    // Timers need a global callback function, it cannot be an instance member of a class... 
    // This makes everything very conmplicated...
    // Currently only one instance is allowed, but it would be easy to extend it to a fixed maximum number of instances
    // globalEchoCheck() is called by the timer; the call is forwarded to HCSR04::instance->echoCheck()    
    static SonarNP* instance; 
    static void globalEchoCheck();
    void echoCheck();
    
    NewPing* sonar;

    // Cyclic buffer of the last readings accumulated for computing the median
    int lastReadings[5];
    // The number of readings to be able to maintain the cyclic buffer
    int nrReadings;
    
    int median(int a, int b, int c, int d, int e);

    // New measurements are initiated sequentially every some microseconds to avoid interference
    long lastMeasureTime;

    // The last computed measurement, so we can return something between two measurements
    int lastMeasure;
};

#endif  // SONARNP_H
