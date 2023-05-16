#include <SDL.h>
#include "game.h"

int actual_tick_delta = TARGET_TICK_DELTA;

// Scaling type: 0=strict, 1=normal, 2=stretched, 3=fixed
int window_scaling_type = 0;
int window_fixed_scale = 1 * WINDOW_SCALE;

void main_render(SDL_Renderer* renderer, SDL_Window* window) {
    
    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            AREA_WIDTH,
            AREA_HEIGHT);
    SDL_SetRenderTarget(renderer, texture);
    
    render(renderer, texture);
    
    SDL_SetRenderTarget(renderer, NULL);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

    if(window_scaling_type == 0) {
        int scale_width = window_width / AREA_WIDTH;
        int scale_height = window_height / AREA_HEIGHT;
        int scale = MIN(scale_width, scale_height);
        
        SDL_Rect draw_area;
        draw_area.w = AREA_WIDTH * scale;
        draw_area.h = AREA_HEIGHT * scale;
        draw_area.x = (window_width  - (AREA_WIDTH  * scale))/2;
        draw_area.y = (window_height - (AREA_HEIGHT * scale))/2;
        
        SDL_RenderCopy(renderer, texture, NULL, &draw_area);
    } else if(window_scaling_type == 1){
        float scale_width = window_width * 1.0 / AREA_WIDTH;
        float scale_height = window_height * 1.0 / AREA_HEIGHT;
        float scale = MIN(scale_width, scale_height);
    
        SDL_Rect draw_area;
        draw_area.w = AREA_WIDTH * scale;
        draw_area.h = AREA_HEIGHT * scale;
        draw_area.x = (int)((window_width  - (AREA_WIDTH  * scale))/2);
        draw_area.y = (int)((window_height - (AREA_HEIGHT * scale))/2);
        
        SDL_RenderCopy(renderer, texture, NULL, &draw_area);
    } else if(window_scaling_type == 2) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    } else if(window_scaling_type == 3) {
        int scale = window_fixed_scale; 

        SDL_Rect draw_area;
        draw_area.w = AREA_WIDTH * scale;
        draw_area.h = AREA_HEIGHT * scale;
        draw_area.x = (window_width  - (AREA_WIDTH  * scale))/2;
        draw_area.y = (window_height - (AREA_HEIGHT * scale))/2;

        SDL_RenderCopy(renderer, texture, NULL, &draw_area);
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
}

void main_handle_event(SDL_Window* window, SDL_Event* event) {
    if(event->type == SDL_KEYDOWN) {
        switch(event->key.keysym.scancode) {
            case SDL_SCANCODE_GRAVE:
                window_scaling_type = (window_scaling_type + 1)%3;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH, AREA_HEIGHT);
                return;
            case SDL_SCANCODE_1:
                window_scaling_type = 3;
                window_fixed_scale = 1 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_2:
                window_scaling_type = 3;
                window_fixed_scale = 2 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_3:
                window_scaling_type = 3;
                window_fixed_scale = 3 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_4:
                window_scaling_type = 3;
                window_fixed_scale = 4 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_5:
                window_scaling_type = 3;
                window_fixed_scale = 5 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_6:
                window_scaling_type = 3;
                window_fixed_scale = 6 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_7:
                window_scaling_type = 3;
                window_fixed_scale = 7 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_8:
                window_scaling_type = 3;
                window_fixed_scale = 8 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_9:
                window_scaling_type = 3;
                window_fixed_scale = 9 * WINDOW_SCALE;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_0:
                window_scaling_type = 3;
                window_fixed_scale = 1;
                SDL_SetWindowMinimumSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                SDL_SetWindowSize(window, AREA_WIDTH*window_fixed_scale, AREA_HEIGHT*window_fixed_scale);
                return;
            case SDL_SCANCODE_RETURN:
                if(!(event->key.keysym.mod & KMOD_ALT)) {
                    break;
                }
            case SDL_SCANCODE_F11:
                if(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) {
                    SDL_SetWindowFullscreen(window, 0);
                } else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
                return;
            default:
                break;
        }
    }
    handle_event(event);
}

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("main 0: %s\n", SDL_GetError());
        goto init_failed;
    }
    
    SDL_Window* window = SDL_CreateWindow(
            "Game",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            AREA_WIDTH*WINDOW_SCALE,
            AREA_HEIGHT*WINDOW_SCALE,
            SDL_WINDOW_RESIZABLE);
    if(window == NULL) {
        printf("main 1: %s\n", SDL_GetError());
        goto window_failed;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(renderer == NULL) {
        printf("main 2: %s\n", SDL_GetError());
        goto renderer_failed;
    }
    
    SDL_SetWindowMinimumSize(window, AREA_WIDTH, AREA_HEIGHT);

    init(renderer);

    SDL_Event event;
    Uint64 time = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                break;
            }
            main_handle_event(window, &event);
        } else {
            int ticks = SDL_GetTicks() - time;
            if(ticks >= actual_tick_delta) {
                time = SDL_GetTicks();
                update(ticks);
                main_render(renderer, window);
            }
        }
    }

    SDL_DestroyRenderer(renderer);
renderer_failed:
    SDL_DestroyWindow(window);
window_failed:
    SDL_Quit();
init_failed:
    return 0;
}



