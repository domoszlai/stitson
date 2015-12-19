#ifndef LIGHT_H
#define LIGHT_H

#include <mthread.h>

class Light : public Thread
{
public:
    Light(int pin);
        
    void start();
    void stop();    
protected:
    bool loop();
private:
    int pin;
};

#endif  // LIGHT_H
