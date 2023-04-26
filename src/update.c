#include <SDL.h>
#include "game.h"

void update(int ticks) {
    gamepad_update(game_controllers);
    return;
}
