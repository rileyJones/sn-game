#include <SDL.h>
#include "game.h"




SDL_Texture** sprite_textures;
tile_data sprites[1024];
background_data backgrounds[4];


void render_sprite(SDL_Renderer* renderer, tile_data* sprite) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(sprite->flip_x) {
        flip = flip | SDL_FLIP_HORIZONTAL;
    }
    if(sprite->flip_y) {
        flip = flip | SDL_FLIP_VERTICAL;
    }
    

    SDL_Rect dest_rect = sprite->dst;
    dest_rect.x /= 16*TARGET_TICK_DELTA; 
    dest_rect.y /= 16*TARGET_TICK_DELTA;
    
    SDL_SetTextureAlphaMod(sprite_textures[sprite->index], sprite->alpha);

    SDL_RenderCopyEx(renderer, sprite_textures[sprite->index], &sprite->src, &dest_rect, sprite->rotation/TARGET_TICK_DELTA, NULL, flip);
}


void render(SDL_Renderer* renderer, SDL_Texture* output) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    for(int p = 3; p >= 0; p--) {
        for(int i = 0; i < 4; i++) {
            if(backgrounds[i].properties.active && backgrounds[i].properties.priority == p) {
                printf("AAAA\n");
                break;
            }
        }
        for(int i = 1023; i >= 0; i--) {
            if(sprites[i].active && sprites[i].priority == p) {
                render_sprite(renderer, sprites+i);
            }
        }
    }
}

