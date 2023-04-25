#include <SDL.h>

#define TARGET_TICK_DELTA 16
int actual_tick_delta = TARGET_TICK_DELTA;

// Scaling type: 0=strict, 1=normal, 2=stretched
int scaling_type = 0;

#define AREA_WIDTH 640
#define AREA_HEIGHT 480
#define WINDOW_SCALE 1

#define MIN(A,B) ((A>B)?B:A)
#define MAX(A,B) ((A>B)?A:B)


void update(int ticks) {
    return;
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawPoint(renderer, 5, 5);
}

void main_render(SDL_Renderer* renderer, SDL_Window* window) {
    
    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            AREA_WIDTH,
            AREA_HEIGHT);
    SDL_SetRenderTarget(renderer, texture);
    
    render(renderer);
    
    SDL_SetRenderTarget(renderer, NULL);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    
    

    if(scaling_type == 0) {
        int scale_width = window_width / AREA_WIDTH;
        int scale_height = window_height / AREA_HEIGHT;
        int scale = MIN(scale_width, scale_height);
    
        SDL_Rect draw_area;
        draw_area.w = AREA_WIDTH * scale;
        draw_area.h = AREA_HEIGHT * scale;
        draw_area.x = (window_width  - (AREA_WIDTH  * scale))/2;
        draw_area.y = (window_height - (AREA_HEIGHT * scale))/2;
        
        SDL_RenderCopy(renderer, texture, NULL, &draw_area);
    } else if(scaling_type == 1){
        float scale_width = window_width * 1.0 / AREA_WIDTH;
        float scale_height = window_height * 1.0 / AREA_HEIGHT;
        float scale = MIN(scale_width, scale_height);
    
        SDL_Rect draw_area;
        draw_area.w = AREA_WIDTH * scale;
        draw_area.h = AREA_HEIGHT * scale;
        draw_area.x = (int)((window_width  - (AREA_WIDTH  * scale))/2);
        draw_area.y = (int)((window_height - (AREA_HEIGHT * scale))/2);
        
        SDL_RenderCopy(renderer, texture, NULL, &draw_area);
    } else if(scaling_type == 2) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
}

void handle_events(SDL_Event* event) {
    return;
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
    SDL_SetWindowMinimumSize(window, AREA_WIDTH, AREA_HEIGHT);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(renderer == NULL) {
        printf("main 2: %s\n", SDL_GetError());
        goto renderer_failed;
    }

    SDL_Event event;
    Uint64 time = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                break;
            }
            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.scancode) {
                    case SDL_SCANCODE_GRAVE:
                        scaling_type = (scaling_type + 1)%3;
                        continue;
                    default:
                        break;
                }
            }
            handle_events(&event);
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



