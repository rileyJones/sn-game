#ifndef GAME_H
#define GAME_H
#include "gamepad.h"

#define TARGET_TICK_DELTA 16

#define AREA_WIDTH 640
#define AREA_HEIGHT 480
#define WINDOW_SCALE 1

#define MIN(A,B) ((A>B)?B:A)
#define MAX(A,B) ((A>B)?A:B)

void update(int ticks);
void render(SDL_Renderer* renderer, SDL_Texture* output);
void handle_event(SDL_Event* event);
void init(SDL_Renderer* renderer);

// specific data:

typedef struct {
    int index;
    int x; int y; int w; int h;
    SDL_bool dirty;
    SDL_bool active;
    SDL_bool flip_x; SDL_bool flip_y;
    double scale; double rotation;
    Uint8 alpha;
    Uint8 priority;
} tile_data;

typedef struct {
    SDL_Texture** textures;
    tile_data* data;
    SDL_bool dirty;
    tile_data properties;
} background_data;

extern gamepad game_controllers[1];

extern SDL_Texture** sprite_textures;
extern tile_data sprites[1024];
extern background_data backgrounds[4];

#endif
