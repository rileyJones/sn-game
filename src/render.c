#include <SDL.h>
#include "render.h"
#include "game.h"



SDL_Texture** sprite_textures;
tile_data sprites[1024];
background_data backgrounds[4];
int hdma = -1;
Uint8 clear_r = 0xFF;
Uint8 clear_g = 0xFF;
Uint8 clear_b = 0xFF;


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

void render_bg(SDL_Renderer* renderer,background_data* background, int v_offset) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(background->properties.flip_x) {
        flip = flip | SDL_FLIP_HORIZONTAL;
    }
    if(background->properties.flip_y) {
        flip = flip | SDL_FLIP_VERTICAL;
    }

    SDL_SetTextureAlphaMod(background->tex, background->properties.alpha);
    
    double size = SDL_sqrt(AREA_WIDTH*AREA_WIDTH + AREA_HEIGHT*AREA_HEIGHT * 1.0)/2
        + SDL_sqrt(
                (background->center.x-AREA_WIDTH/2.0)*(background->center.x-AREA_WIDTH/2.0)
                + (background->center.y-AREA_HEIGHT/2.0)*(background->center.y-AREA_HEIGHT/2.0));

    double size_x = size / background->properties.dst.w;
    double size_y = size / background->properties.dst.h;

    SDL_Point draw_origin;
    draw_origin.x = ((background->properties.dst.x % background->properties.dst.w + background->properties.dst.w) 
         % background->properties.dst.w);
    draw_origin.y = ((background->properties.dst.y % background->properties.dst.h + background->properties.dst.h) 
         % background->properties.dst.h);
    
    for(int x = -size_x - 1; x <= size_x+2; x++) {
        for(int y = -size_y - 1; y <= size_y+2; y++) {
            SDL_Rect dstrect;
            dstrect.x = (x * background->properties.src.w - background->center.x)
                * background->properties.dst.w / background->properties.src.w
                + background->center.x
                + draw_origin.x;
            dstrect.y = (y * background->properties.src.h - background->center.y)
                * background->properties.dst.h / background->properties.src.h
                + background->center.y
                + draw_origin.y
                - v_offset;
            dstrect.w = background->properties.dst.w;
            dstrect.h = background->properties.dst.h;
            
            SDL_Point center;
            center.x = background->center.x - dstrect.x;
            center.y = background->center.y - dstrect.y - v_offset;

            SDL_RenderCopyEx(
                    renderer,
                    background->tex,
                    &background->properties.src,
                    &dstrect,
                    background->properties.rotation,
                    &center,
                    flip);
        }
    }

}


void render_sprite(SDL_Renderer* renderer, tile_data* sprite, int v_offset) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(sprite->flip_x) {
        flip = flip | SDL_FLIP_HORIZONTAL;
    }
    if(sprite->flip_y) {
        flip = flip | SDL_FLIP_VERTICAL;
    }

    SDL_Rect dst_rect;
    dst_rect.x = sprite->dst.x;
    dst_rect.y = sprite->dst.y - v_offset;
    dst_rect.w = sprite->dst.w;
    dst_rect.h = sprite->dst.h;
    
    SDL_SetTextureAlphaMod(sprite_textures[sprite->index], sprite->alpha);

    SDL_RenderCopyEx(renderer, sprite_textures[sprite->index], &sprite->src, &dst_rect, sprite->rotation, NULL, flip);
}


void render(SDL_Renderer* renderer, SDL_Texture* output) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    prerender_bgs(renderer, output);
    int line_num = 0;
    if(hdma == 0) {
        hdma_callback();
    }
    
    while(line_num < AREA_HEIGHT) {
        int end_line;
        if(hdma > line_num) {
            end_line = hdma;
        } else {
            end_line = AREA_HEIGHT;
        }
        
        SDL_Texture* internal_texture = SDL_CreateTexture(
                renderer,
                SDL_PIXELFORMAT_RGBA32,
                SDL_TEXTUREACCESS_TARGET,
                AREA_WIDTH,
                end_line - line_num);
        SDL_SetRenderTarget(renderer, internal_texture);
        SDL_SetRenderDrawColor(renderer, clear_r, clear_g, clear_b, 0xFF);
        SDL_RenderClear(renderer);
        
        for(int p = 3; p >= 0; p--) {
            for(int i = 0; i < 4; i++) {
                if(backgrounds[i].properties.active && backgrounds[i].properties.priority == p) {
                    render_bg(renderer, backgrounds+i, line_num);
                    break;
                }
            }
            for(int i = 1023; i >= 0; i--) {
                if(sprites[i].active && sprites[i].priority == p) {
                    render_sprite(renderer, sprites+i, line_num);
                }
            }
        }

        SDL_Rect dst_rect;
        dst_rect.x = 0;
        dst_rect.y = line_num;
        dst_rect.w = AREA_WIDTH;
        dst_rect.h = end_line - line_num;
        
        SDL_SetRenderTarget(renderer, output);
        SDL_RenderCopy(
                renderer,
                internal_texture,
                NULL,
                &dst_rect);
        
        SDL_DestroyTexture(internal_texture);

        if(end_line == hdma) {
            hdma_callback();
        }
        line_num = end_line;
    }
}

