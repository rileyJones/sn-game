#include <SDL.h>
#include "game.h"

gamepad game_controllers[1];

void init(SDL_Renderer* renderer) {

    hdma = 0;

    gamepad_create(game_controllers, -1);
    gamepad_set_key_button(game_controllers,     SDL_SCANCODE_UP,       SDL_CONTROLLER_BUTTON_DPAD_UP);
    gamepad_set_key_button(game_controllers,   SDL_SCANCODE_DOWN,     SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    gamepad_set_key_button(game_controllers,   SDL_SCANCODE_LEFT,     SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    gamepad_set_key_button(game_controllers,  SDL_SCANCODE_RIGHT,    SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_X,             SDL_CONTROLLER_BUTTON_A);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_Z,             SDL_CONTROLLER_BUTTON_B);
    gamepad_set_key_button(game_controllers, SDL_SCANCODE_RETURN,         SDL_CONTROLLER_BUTTON_START);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_A,  SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    gamepad_set_key_button(game_controllers,      SDL_SCANCODE_S, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

    sprite_textures = malloc(sizeof(SDL_Texture*) * 16);
    SDL_Surface* sprite_surface = SDL_LoadBMP("src/render/data/test.bmp");
    sprite_textures[0] = SDL_CreateTextureFromSurface(
            renderer,
            sprite_surface);
    sprites[105].index = 0;
    sprites[105].active = SDL_FALSE;
    sprites[105].src.x = 0;
    sprites[105].src.y = 0;
    sprites[105].src.w = sprite_surface->w;
    sprites[105].src.h = sprite_surface->h;
    sprites[105].dst.x = 0;
    sprites[105].dst.y = 0;
    sprites[105].dst.w = 64;
    sprites[105].dst.h = 96;
    sprites[105].alpha = 127;
    SDL_FreeSurface(sprite_surface);



    backgrounds[0].textures = malloc(sizeof(SDL_Texture*) * 1);
    SDL_Surface* background_surface = SDL_LoadBMP("src/render/data/tiles.bmp");
    backgrounds[0].textures[0] = SDL_CreateTextureFromSurface(renderer, background_surface);
    backgrounds[0].data = malloc(sizeof(tile_data) * 16 * 16);
    for(int x = 0; x < 16; x++) {
        for(int y = 0; y < 16; y++) {
            backgrounds[0].data[x+16*y].index = 0;
            if(x == 0 || y == 0) {
                backgrounds[0].data[x+16*y].src.x = 0;
                backgrounds[0].data[x+16*y].src.y = 16;
            } else {
                backgrounds[0].data[x+16*y].src.x = 198;
                backgrounds[0].data[x+16*y].src.y = 16;
            }
            backgrounds[0].data[x+16*y].src.w = 16;
            backgrounds[0].data[x+16*y].src.h = 16;
            backgrounds[0].data[x+16*y].dirty = SDL_TRUE;
            backgrounds[0].data[x+16*y].flip_x = SDL_FALSE;
            backgrounds[0].data[x+16*y].flip_y = SDL_FALSE;
        }
    }
    backgrounds[0].tile.w = 16;
    backgrounds[0].tile.h = 16;
    backgrounds[0].map.w = 16;
    backgrounds[0].map.h = 16;
    backgrounds[0].properties.src.x = 0;
    backgrounds[0].properties.src.y = 0;
    backgrounds[0].properties.src.w = 16*16;
    backgrounds[0].properties.src.h = 16*16;
    backgrounds[0].properties.dst.x = 100;
    backgrounds[0].properties.dst.y = 100;
    backgrounds[0].properties.dst.w = 1*16*16;
    backgrounds[0].properties.dst.h = 1*16*16;
    backgrounds[0].properties.dirty = SDL_TRUE;
    backgrounds[0].properties.active = SDL_TRUE;
    backgrounds[0].properties.flip_x = SDL_FALSE;
    backgrounds[9].properties.flip_y = SDL_FALSE;
    backgrounds[0].properties.alpha = 255;
    backgrounds[0].properties.priority = 2;
}


