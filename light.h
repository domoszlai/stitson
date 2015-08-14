#ifndef LIGHT_H
#define LIGHT_H

#include "mthread.h"

class Light : public Thread
{
public:
    Light(int RPin, int GPin, int BPin);
        
    void start();
    void stop();
    
    void set(float r, float g, float b);
    
protected:
    bool loop();
private:
    int RPin;
    int GPin;
    int BPin;

    long state;
};

#endif  // LIGHT_H
