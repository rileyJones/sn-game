#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"

// pre-define
SDL_Color alert_background_color = {0xFF, 0xFF, 0xFF, 0xFF};
SDL_Color alert_text_color = {0x00, 0x00, 0x00, 0xFF};
Uint32 alert_wrap_width = 160;
const char* alert_font_file = "data/munro/munro-narrow.ttf";
int alert_ptsize = 10;
SDL_bool alert_active = SDL_FALSE;

// generated
TTF_Font* alert_font;
SDL_Renderer* alert_renderer;

void alert_init(SDL_Renderer* renderer) {
    if(TTF_Init() < 0) {
        SDL_Quit();
    }
    
    alert_font = TTF_OpenFont(alert_font_file, alert_ptsize);
    if(!alert_font) {
        printf("alert 0: %s\n", SDL_GetError());
        SDL_Quit();
    }
    
    TTF_SetFontHinting(alert_font, TTF_HINTING_NORMAL);
    TTF_SetFontStyle(alert_font, TTF_STYLE_NORMAL);
    TTF_SetFontWrappedAlign(alert_font, TTF_WRAPPED_ALIGN_LEFT);
    
    backgrounds[4].textures = calloc(2, sizeof(SDL_Texture*));
    
    SDL_Surface* blank_surface = SDL_CreateRGBSurfaceWithFormat(
            0,
            1,
            1,
            32,
            SDL_PIXELFORMAT_RGBA8888
        );
    if(!blank_surface) {
        printf("alert 1: %s\n", SDL_GetError());
        SDL_Quit();
    }
    
    backgrounds[4].textures[0] = SDL_CreateTextureFromSurface(
            renderer,
            blank_surface
        );
    if(!backgrounds[4].textures[0]) {
        printf("alert 2: %s\n", SDL_GetError());
        SDL_Quit();
    }
    
    SDL_FreeSurface(blank_surface);
    
    if(0 != SDL_SetTextureBlendMode(
            backgrounds[4].textures[0],
            SDL_BLENDMODE_NONE
        )) {
        printf("alert 3: %s\n", SDL_GetError());
        SDL_Quit();
    }
    
    
    
    backgrounds[4].tex = NULL;
    backgrounds[4].tile.w = TILE_SIZE;
    backgrounds[4].tile.h = TILE_SIZE;
    backgrounds[4].map.w = AREA_WIDTH / TILE_SIZE;
    backgrounds[4].map.h = AREA_HEIGHT / TILE_SIZE;
    backgrounds[4].data = calloc(backgrounds[4].map.h * backgrounds[4].map.w, sizeof(tile_data));
    for(int y = 0; y < backgrounds[4].map.h; y++) {
        for(int x = 0; x < backgrounds[4].map.w; x++) {
            int index = x + backgrounds[4].map.w * y;
            backgrounds[4].data[index].index = 0;
            backgrounds[4].data[index].src.x = 0;
            backgrounds[4].data[index].src.y = 0;
            backgrounds[4].data[index].src.w = 0;
            backgrounds[4].data[index].src.h = 0;
            backgrounds[4].data[index].dirty = SDL_FALSE;
            backgrounds[4].data[index].flip_x = SDL_FALSE;
            backgrounds[4].data[index].flip_y = SDL_FALSE;
        }
    }
    backgrounds[4].center.x = AREA_WIDTH / 2;
    backgrounds[4].center.y = AREA_HEIGHT / 2;
    
    backgrounds[4].properties.src.x = 0;
    backgrounds[4].properties.src.y = 0;
    backgrounds[4].properties.src.w = AREA_WIDTH;
    backgrounds[4].properties.src.h = AREA_HEIGHT;
    backgrounds[4].properties.dst = backgrounds[4].properties.src;
    backgrounds[4].properties.dirty = SDL_TRUE;
    backgrounds[4].properties.active = SDL_FALSE;
    backgrounds[4].properties.flip_x = SDL_FALSE;
    backgrounds[4].properties.flip_y = SDL_FALSE;
    backgrounds[4].properties.rotation = 0;
    backgrounds[4].properties.alpha = 0xFF;
    backgrounds[4].properties.priority = 0;
    
    alert_renderer = renderer;
}

void alert_quit() {
    SDL_DestroyTexture(backgrounds[4].textures[0]);
    SDL_DestroyTexture(backgrounds[4].textures[1]);
    
    free(backgrounds[4].textures);
    free(backgrounds[4].data);
    SDL_DestroyTexture(backgrounds[4].tex);
    
    TTF_CloseFont(alert_font);
    TTF_Quit();
}


void alert(char* text) {
    SDL_Texture* current_target = SDL_GetRenderTarget(alert_renderer);

    SDL_Surface* alert_text_surface = TTF_RenderUTF8_Blended_Wrapped(
            alert_font, 
            text, 
            alert_text_color, 
            alert_wrap_width
        );
    if(!alert_text_surface) {
        printf("alert 4: %s\n", SDL_GetError());
        return;
    }
        
    SDL_Texture* alert_text_middle_texture = SDL_CreateTextureFromSurface(
            alert_renderer,
            alert_text_surface
        );
    if(!alert_text_middle_texture) {
        printf("alert 5: %s\n", SDL_GetError());
        return;
    }
    
    
    SDL_DestroyTexture(backgrounds[4].textures[1]);
    backgrounds[4].textures[1] = SDL_CreateTexture(
            alert_renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            ((alert_text_surface->w+1) / backgrounds[4].tile.w + 1) * backgrounds[4].tile.w,
            ((alert_text_surface->h+1) / backgrounds[4].tile.h + 1) * backgrounds[4].tile.h
        );
    if(!backgrounds[4].textures[1]) {
        printf("alert 6: %s\n", SDL_GetError());
        return;
    }
    
    SDL_Rect draw_rect;
    draw_rect.x = 1;
    draw_rect.y = 1;
    draw_rect.w = alert_text_surface->w;
    draw_rect.h = alert_text_surface->h;
    
    SDL_FreeSurface(alert_text_surface);
    
    if(0 != SDL_SetRenderTarget(alert_renderer, backgrounds[4].textures[1])) {
        printf("alert 7: %s\n", SDL_GetError());
        return;
    }
    if(0 != SDL_SetRenderDrawColor(
            alert_renderer, 
            alert_background_color.r,
            alert_background_color.g,
            alert_background_color.b,
            alert_background_color.a
        )) {
        printf("alert 8: %s\n", SDL_GetError());
        return;
    }
    if(0 != SDL_RenderClear(alert_renderer)) {
        printf("alert 9: %s\n", SDL_GetError());
        return;
    }
    if(0 != SDL_RenderCopy(alert_renderer, alert_text_middle_texture, NULL, &draw_rect)) {
        printf("alert 10: %s\n", SDL_GetError());
        return;
    }
    
    SDL_DestroyTexture(alert_text_middle_texture);
    
    int offset_x = ((draw_rect.w+1) / backgrounds[4].tile.w + 1);
    int offset_y = ((draw_rect.h+1) / backgrounds[4].tile.h + 1);
    
    int max_x = backgrounds[4].map.w / 2 + offset_x / 2;
    int min_x = max_x - offset_x;
    int min_y = backgrounds[4].map.h / 2;
    int max_y = min_y + offset_y;
    
    for(int y = 0; y < backgrounds[4].map.h; y++) {
        for(int x = 0; x < backgrounds[4].map.w; x++) {
            int index = x + backgrounds[4].map.w * y;
            if(x >= min_x && x < max_x && y >=min_y && y < max_y) {
                backgrounds[4].data[index].index = 1;
                backgrounds[4].data[index].src.x = (x - min_x) * backgrounds[4].tile.w;
                backgrounds[4].data[index].src.y = (y - min_y) * backgrounds[4].tile.h;
                backgrounds[4].data[index].src.w = backgrounds[4].tile.w;
                backgrounds[4].data[index].src.h = backgrounds[4].tile.h;
                backgrounds[4].data[index].dirty = SDL_TRUE;
                backgrounds[4].data[index].flip_x = SDL_FALSE;
                backgrounds[4].data[index].flip_y = SDL_FALSE;
            } else {
                if(backgrounds[4].data[index].index == 0) {
                    continue;
                } else {
                    backgrounds[4].data[index].index = 0;
                    backgrounds[4].data[index].src.x = 0;
                    backgrounds[4].data[index].src.y = 0;
                    backgrounds[4].data[index].src.w = 1;
                    backgrounds[4].data[index].src.h = 1;
                    backgrounds[4].data[index].dirty = SDL_TRUE;
                    backgrounds[4].data[index].flip_x = SDL_FALSE;
                    backgrounds[4].data[index].flip_y = SDL_FALSE;
                }
            }
        }
    }
    backgrounds[4].properties.active = SDL_TRUE;
    alert_active = SDL_TRUE;
    
    if(0 != SDL_SetRenderTarget(alert_renderer, current_target)) {
        printf("alert 11: %s\n", SDL_GetError());
        return;
    }
}





