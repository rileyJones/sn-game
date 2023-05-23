#include <SDL.h>
#include "game.h"



void hdma_callback() {

}



void update(int ticks) {
    gamepad_update(game_controllers);
    if(!alert_active) {
        alert("Hello World!!!");
    } else {
        //printf("Hiya!\n");
    }
}
