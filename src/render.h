#ifndef RENDER_H
#define RENDER_H

typedef struct {
    int index;
    SDL_Rect src;
    SDL_Rect dst;
    SDL_bool dirty;
    SDL_bool active;
    SDL_bool flip_x, flip_y;
    double rotation;
    Uint8 alpha;
    Uint8 priority;
} tile_data;

typedef struct {
    SDL_Texture** textures;
    tile_data* data;
    SDL_bool dirty;
    tile_data properties;
} background_data;

extern SDL_Texture** sprite_textures;
extern tile_data sprites[1024];
extern background_data backgrounds[4];

#endif
