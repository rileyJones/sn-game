#include <SDL.h>
#include "game.h"



void hdma_callback() {

}


int alert_count = 0;

void update(int ticks) {
    gamepad_update(game_controllers);


    if(alert_active) {
        if(gamepad_button_pressed(game_controllers, SDL_CONTROLLER_BUTTON_A)) {
            alert_disable();
        }
    } else {
        if(gamepad_button_pressed(game_controllers, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
            char alert_text[14];
            alert_count++;
            snprintf(alert_text, 14, "TEST ALERT %2d", alert_count);
            alert(alert_text);
        }
    }
}
