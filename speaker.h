#ifndef SPEAKER_H
#define SPEAKER_H

#include "mthread.h"

enum Melody
{
    SIREN,
    MELODY1
};    

class Speaker : public Thread
{
public:
    Speaker(int speakerPin);
        
    void play(Melody melody, int count); // -1 means until stop
    void stop();
    
protected:
    bool loop();
private:
    int speakerPin;
    Melody melody;
    int count;
    long state;
    
    Melody nextMelody;
    int nextCount;
    
    void countDown();
};

#endif  // SPEAKER_H
