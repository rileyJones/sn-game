#include <SDL.h>
#include "game.h"

void update(int ticks) {
    gamepad_update(game_controllers);
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
        sprites[105].dst.y -= 24*ticks;
    }
    
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
        sprites[105].dst.y += 24*ticks;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
        sprites[105].dst.x -= 24*ticks;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        sprites[105].dst.x += 24*ticks;
    }
    
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_B)) {
        sprites[105].rotation -= ticks;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_A)) {
        sprites[105].rotation += ticks;
    }
    return;
}
