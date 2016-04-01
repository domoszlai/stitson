#ifndef ACS712_H
#define ACS712_H

#include <mthread.h>

#define MVPERAMP 100 // use 185 for 5A, 100 for 20A Module and 66 for 30A Module

class ACS712 : public Thread
{
public:
    ACS712(int pin);
protected:
    bool loop();
private:
    int pin;
};

#endif  // ACS712_H
