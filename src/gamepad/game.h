#ifndef GAME_H
#define GAME_H
#include "gamepad.h"

#define TARGET_TICK_DELTA 100

#define AREA_WIDTH 640
#define AREA_HEIGHT 480
#define WINDOW_SCALE 1

#define MIN(A,B) ((A>B)?B:A)
#define MAX(A,B) ((A>B)?A:B)

void update(int ticks);
void render(SDL_Renderer* renderer);
void handle_event(SDL_Event* event);
void init();

extern gamepad game_controllers[1];

#endif
