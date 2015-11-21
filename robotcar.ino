#include "mthread.h"
#include "wheel.h"
#include "command.h"
#include "speaker.h"
#include "light.h"
#include "serialinput.h"
#include "ps2input.h"

Wheel RR(5, 34, 32);
Wheel RL(4, 30, 28);
Wheel FR(2, 38, 36);
Wheel FL(3, 42, 40);

HCSR04 D(A0,A1);
Speaker speaker(A2);
Light light(6,7,8);

Command command(&FL,&FR,&RL,&RR,&speaker,&D,&light);

void setup()
{
    // Initialize the serial connection. Does not work witg PS2 controller
    Serial.begin(9600);

//    light.set(0,1.0,0);
//    delay(1000);
//    light.set(0,0,0);
        
    main_thread_list->add_thread(&FL);  
    main_thread_list->add_thread(&FR);  
    main_thread_list->add_thread(&RL);
    main_thread_list->add_thread(&RR);  
    main_thread_list->add_thread(&speaker);
    main_thread_list->add_thread(&command); 
    main_thread_list->add_thread(&light);
    
//    main_thread_list->add_thread(new SerialInput(&command));
    main_thread_list->add_thread(new PS2Input(50,48,46,44, &command));   
}


