#ifndef RENDER_H
#define RENDER_H

typedef struct {
    int index;                  // TILE,     SPRITE
    SDL_Rect src;               // TILE, BG, SPRITE
    SDL_Rect dst;               //       BG, SPRITE
    SDL_bool dirty;             // TILE, BG
    SDL_bool active;            //       BG, SPRITE
    SDL_bool flip_x, flip_y;    // TILE, BG, SPRITE
    double rotation;            //       BG, SPRITE
    Uint8 alpha;                //       BG, SPRITE
    Uint8 priority;             //       BG, SPRITE
} tile_data;

typedef struct {
    SDL_Texture** textures;
    SDL_Texture* tex;           // INTERNAL USE ONLY
    tile_data* data;
    SDL_Rect tile;              // W+H, NO X+Y
    SDL_Rect map;               // W+H, NO X+Y
    tile_data properties;
} background_data;

extern SDL_Texture** sprite_textures;
extern tile_data sprites[1024];
extern background_data backgrounds[4];

#endif
