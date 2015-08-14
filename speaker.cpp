#include "mthread.h"
#include "speaker.h"
#include "pitches.h"
#include "NewTone.h"

Speaker::Speaker(int speakerPin)
{
    this->speakerPin = speakerPin;
    this->nextCount = 0;
    
    pinMode(speakerPin,OUTPUT);
}

void Speaker::play(Melody melody, int count)
{
    if(this->melody == melody) 
    {
        this->count += count;  
    }
    else
    {
        if(this->count > 0)
        {
            // wait until the current one finishes, queue the new one
            // if the queue has the same melody, increment the count,
            // otherwise replace it
            if(this->nextMelody == melody)
            {
                this->nextCount += count;
            }
            else
            {
                this->nextMelody = melody;
                this->nextCount = count;
            }
        }
        else if(this->count == -1)
        {
            // the current one is playing forever, make it stoppped after 1 iteration
            this->nextMelody = melody;
            this->nextCount = count;
            this->count = 1;  
        }        
        else
        {
            // nothing is played, start this one
            this->melody = melody;
            this->count = count;
            this->state = 0;
        }
    }
}

void Speaker::countDown()
{
    this->state = 0;
    if(this->count > 0) this->count --;
    
    // start to play the queued one if count became 0
    if(this->count == 0 && this->nextCount != 0)
    {
        this->melody = this->nextMelody;
        this->count = this->nextCount;  
        this->nextCount = 0;
    }
}

void Speaker::stop()
{
    this->count = 0; 
}

bool Speaker::loop()
{
    if(this->count != 0)
    {
        if(melody == SIREN)
        {
            int wait = 1;
            int time = 10;            
          
            if(this->state == 0) this->state = 150; // start at freq 150

            if(this->state <= 1800) // go up to 1800
            {
                NewTone(speakerPin, this->state++, time);  // Beep pin, freq, time
                sleep_milli(wait);
            }
            else if(this->state > 1800 && this->state < 1800 + 1800 - 150) // go down to 150
            {
                NewTone(speakerPin, 1800 - (this->state - 1800), time);
                sleep_milli(wait);
                this->state++;
            }
            else
            {
                countDown();
            }
        }
        else if(melody == MELODY1)
        {
            int melody[] = {
              NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
            
            // note durations: 4 = quarter note, 8 = eighth note, etc.:
            int noteDurations[] = {
              4, 8, 8, 4, 4, 4, 4, 4 };          

            // stop the tone playing:
            noNewTone(speakerPin);

            int thisNote = state++;
      
            if(thisNote < 8) // number of notes
            {
                // to calculate the note duration, take one second 
                // divided by the note type.
                //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
                int noteDuration = 1000/noteDurations[thisNote];
                NewTone(speakerPin, melody[thisNote], noteDuration);
            
                // to distinguish the notes, set a minimum time between them.
                // the note's duration + 30% seems to work well:
                int pauseBetweenNotes = noteDuration * 1.30;
                sleep_milli(pauseBetweenNotes);
            }
            else
            {
                countDown();
            }              
        }
    }
    return true;
}

