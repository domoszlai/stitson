#include "mthread.h"
#include "wheel.h"
#include "command.h"
#include "speaker.h"
#include "light.h"
#include "serialinput.h"

// PWM pins: 3,5,6,9,10,11

// Same speed pin, must be PWM
Wheel RR(11, 12, 4);
Wheel FR(11, 7, 8);
Wheel FL(11, A3, A4);
Wheel RL(11, 13, 2);

HCSR04 D(A2,A1);

Speaker speaker(A0);

Light light = Light(6,5,3);

Command command(&FL,&FR,&RL,&RR,&speaker,&D,&light);

void setup()
{
    // Initialize the serial connection:
    Serial.begin(9600);

    light.set(0,1.0,0);
    delay(1000);
    light.set(0,0,0);
        
    main_thread_list->add_thread(&FL);  
    main_thread_list->add_thread(&FR);  
    main_thread_list->add_thread(&RL);
    main_thread_list->add_thread(&RR);  
    main_thread_list->add_thread(&speaker);
    main_thread_list->add_thread(&command); 
    main_thread_list->add_thread(&light);
    
    main_thread_list->add_thread(new SerialInput(&command));    
    
//    command.setMaxMovementTime(500);
//    command.turnLeft();
//    command.play(MELODY1, 2);
  
    //BL.goForward();
    //delay(500);
    //BL.setSpeed(0.2);    
}


