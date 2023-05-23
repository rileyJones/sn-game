#include <SDL.h>
#include "game.h"



void hdma_callback() {

}


int delay = -1;


void update(int ticks) {
    gamepad_update(game_controllers);
    if(!alert_active) {
        alert("Hello World!!!");
        delay = 0;
    } else {
        delay += ticks;
        if(delay > 3000 && delay < 5000) {
            delay = 7000;
            alert("Hi");
        }
        //printf("Hiya!\n");
    }
}
