#include <SDL.h>
#include "game.h"



void hdma_callback() {

}



void update(int ticks) {
    gamepad_update(game_controllers);
}
