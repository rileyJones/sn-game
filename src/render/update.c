#include <SDL.h>
#include "game.h"


double movement_x, movement_y;

void hdma_callback() {
    if(hdma >= 200) {
        if(hdma == 200) {
            //printf("%d\n", backgrounds[0].properties.dst.y);
        }
        backgrounds[0].properties.active = SDL_TRUE;
        backgrounds[0].properties.dst.w = (3*hdma - 590);
        backgrounds[0].properties.dst.h = (3*hdma - 590);
        backgrounds[0].properties.dst.x = movement_x*backgrounds[0].properties.dst.w/16/16;
        backgrounds[0].properties.dst.y = movement_y*backgrounds[0].properties.dst.h/16/16;
        hdma++;
        //backgrounds[0].properties.dst.x = movement_x;
        //backgrounds[0].properties.dst.y = movement_y;
        if(hdma == AREA_HEIGHT) {
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
        movement_x += SDL_sin(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
        movement_y += SDL_cos(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
    }
    
    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
        movement_x -= SDL_sin(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
        movement_y -= SDL_cos(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
        movement_x += SDL_cos(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
        movement_y -= SDL_sin(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        movement_x -= SDL_cos(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
        movement_y += SDL_sin(backgrounds[0].properties.rotation * PI / 180) * 24.0 * ticks / TARGET_TICK_DELTA / 16;
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
        //backgrounds[0].properties.dst.w *= 100.0 * ticks / 99 / TARGET_TICK_DELTA;
        //backgrounds[0].properties.dst.h *= 100.0 * ticks / 99 / TARGET_TICK_DELTA;
        hdma += 1;
    }

    if(gamepad_button_held(game_controllers, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
        //backgrounds[0].properties.dst.w *= 99.0 * ticks / 100 / TARGET_TICK_DELTA;
        //backgrounds[0].properties.dst.h *= 99.0 * ticks / 100 / TARGET_TICK_DELTA;
        hdma -= 1;
    }


}
