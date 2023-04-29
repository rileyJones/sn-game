#include <SDL.h>
#include "game.h"

void hdma_callback() {
    if(hdma >= 200) {
        backgrounds[0].properties.active = SDL_TRUE;
        backgrounds[0].properties.dst.w = hdma * hdma / 200;
        hdma++;
        if(hdma >= AREA_HEIGHT) {
            hdma = 0;
        }
    } else if(hdma == 0) {
        backgrounds[0].properties.active = SDL_FALSE;
        hdma = 200;
    }
}



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

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
        backgrounds[0].properties.dst.w *= 100.0 * ticks / 99 / TARGET_TICK_DELTA;
        backgrounds[0].properties.dst.h *= 100.0 * ticks / 99 / TARGET_TICK_DELTA;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
        backgrounds[0].properties.dst.w *= 99.0 * ticks / 100 / TARGET_TICK_DELTA;
        backgrounds[0].properties.dst.h *= 99.0 * ticks / 100 / TARGET_TICK_DELTA;
    }


}
