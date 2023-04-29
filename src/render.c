#include <SDL.h>
#include "render.h"
#include "game.h"



SDL_Texture** sprite_textures;
tile_data sprites[1024];
background_data backgrounds[4];


void prerender_bgs(SDL_Renderer* renderer, SDL_Texture* output) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    for(int i = 0; i < 4; i++) {
        if(!backgrounds[i].properties.active) {
            continue;
        }
        if(backgrounds[i].properties.dirty) {
            SDL_DestroyTexture(backgrounds[i].tex);
            backgrounds[i].tex = SDL_CreateTexture(
                    renderer,
                    SDL_PIXELFORMAT_RGBA32,
                    SDL_TEXTUREACCESS_TARGET,
                    backgrounds[i].tile.w * backgrounds[i].map.w,
                    backgrounds[i].tile.h * backgrounds[i].map.h);
            SDL_RenderClear(renderer);
        }
        SDL_SetRenderTarget(renderer, backgrounds[i].tex);
        for(int x = 0; x < backgrounds[i].map.w; x++) {
            for(int y = 0; y < backgrounds[i].map.h; y++) {
                int index = x + y * backgrounds[i].map.w;
                if(backgrounds[i].properties.dirty || backgrounds[i].data[index].dirty) {
                    SDL_RendererFlip flip = SDL_FLIP_NONE;
                    if(backgrounds[i].data[index].flip_x) {
                        flip = flip | SDL_FLIP_HORIZONTAL;
                    }
                    if(backgrounds[i].data[index].flip_y) {
                        flip = flip | SDL_FLIP_VERTICAL;
                    }

                    SDL_Rect draw_dst;
                    draw_dst.x = x * backgrounds[i].tile.w;
                    draw_dst.y = y * backgrounds[i].tile.h;
                    draw_dst.w = backgrounds[i].tile.w;
                    draw_dst.h = backgrounds[i].tile.h;

                    SDL_RenderCopyEx(
                            renderer, 
                            backgrounds[i].textures[backgrounds[i].data[index].index],
                            &backgrounds[i].data[index].src,
                            &draw_dst,
                            0.0,
                            NULL,
                            flip);
                    backgrounds[i].data[index].dirty = SDL_FALSE;
                }
            }
        }
        backgrounds[i].properties.dirty = SDL_FALSE;
    }

    SDL_SetRenderTarget(renderer, output);
}

void render_bg(SDL_Renderer* renderer,background_data* background) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(background->properties.flip_x) {
        flip = flip | SDL_FLIP_HORIZONTAL;
    }
    if(background->properties.flip_y) {
        flip = flip | SDL_FLIP_VERTICAL;
    }

    SDL_SetTextureAlphaMod(background->tex, background->properties.alpha);
    
    double size = sqrt(AREA_WIDTH*AREA_WIDTH + AREA_HEIGHT*AREA_HEIGHT * 1.0);
    double off_x = size / background->properties.dst.w / 2;
    double off_y = size / background->properties.dst.h / 2;
    for(int x = -off_x - 2; x <= off_x; x++) {
        for(int y = -off_y - 2; y <= off_y; y++) {
            SDL_Rect dst_rect;
            dst_rect.x = (background->properties.dst.x % background->properties.dst.w + background->properties.dst.w) 
                % background->properties.dst.w 
                + AREA_WIDTH / 2
                + x * background->properties.dst.w;
            
            dst_rect.y = (background->properties.dst.y % background->properties.dst.h + background->properties.dst.h) 
                % background->properties.dst.h 
                + AREA_HEIGHT / 2
                + y * background->properties.dst.h;

            dst_rect.w = background->properties.dst.w;
            dst_rect.h = background->properties.dst.h;

            SDL_Point rot_point;
            rot_point.x = AREA_WIDTH  / 2 - dst_rect.x;
            rot_point.y = AREA_HEIGHT / 2 - dst_rect.y;
            
            SDL_RenderCopyEx(
                    renderer,
                    background->tex,
                    &background->properties.src,
                    &dst_rect,
                    background->properties.rotation,
                    &rot_point,
                    flip);
        }
    }
}


void render_sprite(SDL_Renderer* renderer, tile_data* sprite) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(sprite->flip_x) {
        flip = flip | SDL_FLIP_HORIZONTAL;
    }
    if(sprite->flip_y) {
        flip = flip | SDL_FLIP_VERTICAL;
    }
    
    SDL_SetTextureAlphaMod(sprite_textures[sprite->index], sprite->alpha);

    SDL_RenderCopyEx(renderer, sprite_textures[sprite->index], &sprite->src, &sprite->dst, sprite->rotation, NULL, flip);
}


void render(SDL_Renderer* renderer, SDL_Texture* output) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    prerender_bgs(renderer, output);

    for(int p = 3; p >= 0; p--) {
        for(int i = 0; i < 4; i++) {
            if(backgrounds[i].properties.active && backgrounds[i].properties.priority == p) {
                render_bg(renderer, backgrounds+i);
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

