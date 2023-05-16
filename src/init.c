#include <SDL.h>
#include "game.h"

gamepad game_controllers[1];

void init(SDL_Renderer* renderer) {
    
    hdma = -1;

    gamepad_create(game_controllers, -1);
    gamepad_set_key_button(game_controllers,         SDL_SCANCODE_UP,       SDL_CONTROLLER_BUTTON_DPAD_UP);
    gamepad_set_key_button(game_controllers,       SDL_SCANCODE_DOWN,     SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    gamepad_set_key_button(game_controllers,       SDL_SCANCODE_LEFT,     SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_RIGHT,    SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    gamepad_set_key_button(game_controllers,          SDL_SCANCODE_X,             SDL_CONTROLLER_BUTTON_A);
    gamepad_set_key_button(game_controllers,          SDL_SCANCODE_Z,             SDL_CONTROLLER_BUTTON_B);
    gamepad_set_key_button(game_controllers,     SDL_SCANCODE_RETURN,         SDL_CONTROLLER_BUTTON_START);
    gamepad_set_key_button(game_controllers, SDL_SCANCODE_APOSTROPHE,          SDL_CONTROLLER_BUTTON_BACK);
    gamepad_set_key_button(game_controllers,          SDL_SCANCODE_A,  SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    gamepad_set_key_button(game_controllers,          SDL_SCANCODE_S, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

}


