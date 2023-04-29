#include <SDL.h>
#include "game.h"

void render(SDL_Renderer* renderer, SDL_Texture* output) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    return;
}

