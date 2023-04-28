#include <SDL.h>
#include "game.h"

gamepad game_controllers[1];

void init(SDL_Renderer* renderer) {
    gamepad_create(game_controllers, -1);
    gamepad_set_key_button(game_controllers,     SDL_SCANCODE_UP,    SDL_CONTROLLER_BUTTON_DPAD_UP);
    gamepad_set_key_button(game_controllers,   SDL_SCANCODE_DOWN,  SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    gamepad_set_key_button(game_controllers,   SDL_SCANCODE_LEFT,  SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    gamepad_set_key_button(game_controllers,  SDL_SCANCODE_RIGHT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_X,          SDL_CONTROLLER_BUTTON_A);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_Z,          SDL_CONTROLLER_BUTTON_B);
    gamepad_set_key_button(game_controllers, SDL_SCANCODE_RETURN,      SDL_CONTROLLER_BUTTON_START);

    sprite_textures = malloc(sizeof(SDL_Texture*) * 16);
    SDL_Surface* sprite_surface = SDL_LoadBMP("data/test.bmp");
    sprite_textures[0] = SDL_CreateTextureFromSurface(
            renderer,
            sprite_surface);
    SDL_FreeSurface(sprite_surface);
    sprites[105].index = 0;
    sprites[105].active = SDL_TRUE;
    sprites[105].x = 0;
    sprites[105].y = 0;
    sprites[105].w = 64;
    sprites[105].h = 64;
}


