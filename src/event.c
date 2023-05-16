#include <SDL.h>
#include "game.h"

void handle_event(SDL_Event* event) {
    switch(event->type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            gamepad_trydo_key(
                    game_controllers, 
                    event->key.keysym.scancode,
                    event->key.state,
                    event->key.timestamp);
            break;
        case SDL_CONTROLLERAXISMOTION:
            break;
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            break;
        case SDL_CONTROLLERDEVICEADDED:
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            break;
        case SDL_CONTROLLERDEVICEREMAPPED:
            break;
        default:
            break;
    }
    return;
}
