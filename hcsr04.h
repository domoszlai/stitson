#ifndef HCSR04_H
#define HCSR04_H

class HCSR04
{
public:
    HCSR04(int triggerPin, int echoPin);
        
    long measure();
    
protected:
    bool loop();
private:
    int triggerPin;
    int echoPin;
};

#endif  // HCSR04_H
