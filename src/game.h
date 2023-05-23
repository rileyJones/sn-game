#ifndef GAME_H
#define GAME_H
#include "gamepad.h"
#include "render.h"
#include "alert.h"

#define TARGET_TICK_DELTA 16

#define AREA_WIDTH 240
#define AREA_HEIGHT 160
#define WINDOW_SCALE 3
#define TILE_SIZE 8

#define MIN(A,B) ((A>B)?B:A)
#define MAX(A,B) ((A>B)?A:B)

#define PI 3.14159265359

void update(int ticks);
void render(SDL_Renderer* renderer, SDL_Texture* output);
void handle_event(SDL_Event* event);
void init(SDL_Renderer* renderer);
void quit();

// specific data:

extern gamepad game_controllers[1];


#endif
