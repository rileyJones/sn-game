#include <SDL.h>
#include "game.h"

void update(int ticks) {
    gamepad_update(game_controllers);
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
        sprites[105].y -= 24*ticks;
    }
    
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
        sprites[105].y += 24*ticks;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
        sprites[105].x -= 24*ticks;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        sprites[105].x += 24*ticks;
    }
    return;
}
