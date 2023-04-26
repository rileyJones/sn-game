#include <SDL.h>
#include "game.h"

void set_color(SDL_Renderer* renderer, Uint8 button) {
    if(gamepad_button_repressed(game_controllers, button, 500)) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    } else if(gamepad_button_pressed(game_controllers, button)) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    } else if(gamepad_button_released(game_controllers, button)) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    } else if(gamepad_button_held(game_controllers, button)) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x60, 0xFF);
    } else {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    }
}



void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    //SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    //SDL_RenderDrawPoint(renderer, 5, 5);

    SDL_Rect draw_rect;
    draw_rect.w = 80;
    draw_rect.h = 80;
    
    draw_rect.x = 130;
    draw_rect.y = 110;
    set_color(renderer, SDL_CONTROLLER_BUTTON_DPAD_UP);
    SDL_RenderFillRect(renderer, &draw_rect);

    draw_rect.x =  30;
    draw_rect.y = 210;
    set_color(renderer, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    SDL_RenderFillRect(renderer, &draw_rect);

    draw_rect.x = 130;
    draw_rect.y = 310;
    set_color(renderer, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    SDL_RenderFillRect(renderer, &draw_rect);

    draw_rect.x = 230;
    draw_rect.y = 210;
    set_color(renderer, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    SDL_RenderFillRect(renderer, &draw_rect);
    
    draw_rect.x = 330;
    draw_rect.y = 110;
    set_color(renderer, SDL_CONTROLLER_BUTTON_START);
    SDL_RenderFillRect(renderer, &draw_rect);

    draw_rect.x = 430;
    draw_rect.y = 210;
    set_color(renderer, SDL_CONTROLLER_BUTTON_B);
    SDL_RenderFillRect(renderer, &draw_rect);

    draw_rect.x = 530;
    draw_rect.y = 210;
    set_color(renderer, SDL_CONTROLLER_BUTTON_A);
    SDL_RenderFillRect(renderer, &draw_rect);

}

