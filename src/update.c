#include <SDL.h>
#include "game.h"

void update(int ticks) {
    gamepad_update(game_controllers);
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
        //sprites[105].dst.y -= 24*ticks/TARGET_TICK_DELTA/16;
        backgrounds[0].properties.dst.y -= 24*ticks/TARGET_TICK_DELTA/16;
    }
    
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
        //sprites[105].dst.y += 24*ticks/TARGET_TICK_DELTA/16;
        backgrounds[0].properties.dst.y += 24*ticks/TARGET_TICK_DELTA/16;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
        //sprites[105].dst.x -= 24*ticks/TARGET_TICK_DELTA/16;
        backgrounds[0].properties.dst.x -= 24*ticks/TARGET_TICK_DELTA/16;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        //sprites[105].dst.x += 24*ticks/TARGET_TICK_DELTA/16;
        backgrounds[0].properties.dst.x += 24*ticks/TARGET_TICK_DELTA/16;
    }
    
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_B)) {
        //sprites[105].rotation -= ticks/TARGET_TICK_DELTA;
        backgrounds[0].properties.rotation -= ticks/TARGET_TICK_DELTA;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_A)) {
        //sprites[105].rotation += ticks/TARGET_TICK_DELTA;
        backgrounds[0].properties.rotation += ticks/TARGET_TICK_DELTA;
    }
    return;
}
