#include <SDL.h>
#include "gamepad.h"

void gamepad_create(gamepad* controller, SDL_JoystickID joystick_id) {
    controller->joystick_id = joystick_id;
    Uint32 time_now = SDL_GetTicks();

    memset(controller->button_pressed_timestamp, time_now, sizeof(Uint32) * 16 * GAMEPAD_HISTORY);
    memset(controller->button_released_timestamp, time_now, sizeof(Uint32) * 16 * GAMEPAD_HISTORY);
    memset(controller->button_state, SDL_RELEASED, sizeof(Uint8) * 16 * 3);
    
    memset(controller->key_buttons, SDL_SCANCODE_UNKNOWN, sizeof(SDL_Scancode) * 16);

    memset(controller->axis_timestamp, time_now, sizeof(Uint32) * 7 * GAMEPAD_HISTORY);
    memset(controller->axis_state, 0, sizeof(Sint16) * 7 * GAMEPAD_HISTORY);
}

void gamepad_set_key_button(
        gamepad* controller, 
        SDL_Scancode scancode, 
        Uint8 button) {
    controller->key_buttons[button] = scancode;
}

SDL_bool gamepad_button_pressed(gamepad* controller, Uint8 button) {
    if(!controller) return SDL_FALSE;
    if(button >= 16) return SDL_FALSE;
    
    return (controller->button_state[1][button] == SDL_PRESSED) &&
        (controller->button_state[2][button] == SDL_RELEASED);
}

SDL_bool gamepad_button_held(gamepad* controller, Uint8 button) {
    if(!controller) return SDL_FALSE;
    if(button >= 16) return SDL_FALSE;

    return controller->button_state[1][button] == SDL_PRESSED;
}

SDL_bool gamepad_button_released(gamepad* controller, Uint8 button) {
    if(!controller) return SDL_FALSE;
    if(button >= 16) return SDL_FALSE;
    
    return (controller->button_state[1][button] == SDL_RELEASED) &&
        (controller->button_state[2][button] == SDL_PRESSED);
}

SDL_bool gamepad_button_repressed(gamepad* controller, Uint8 button, Uint32 delta) {
    if(!controller) return SDL_FALSE;
    if(button >= 16) return SDL_FALSE;
    if(GAMEPAD_HISTORY < 2) return SDL_FALSE;
    
    return gamepad_button_pressed(controller, button) &&
        (controller->button_pressed_timestamp[button][0] - controller->button_pressed_timestamp[button][1] >= delta);
}

void gamepad_update(gamepad* controller) {
    if(!controller) return;

    memmove(controller->button_state[1], controller->button_state[0], sizeof(Uint8) * 2 * 16);
    memset(controller->button_state[0], SDL_RELEASED, sizeof(Uint8) * 16);
    return;
}

void gamepad_trydo_button(gamepad* controller, SDL_JoystickID joystick_id, Uint8 button, Uint8 action, Uint32 timestamp) {
    if(!controller) return;
    if(controller->joystick_id != joystick_id) return;
    if(button >= 16) return;

    controller->button_state[0][button] = action;
    
    if(action == SDL_PRESSED) {
        if(GAMEPAD_HISTORY >= 2) {
            memmove(
                    controller->button_pressed_timestamp[button]+1, 
                    controller->button_pressed_timestamp[button],
                    sizeof(Uint32) * (GAMEPAD_HISTORY - 1));
            }
        controller->button_pressed_timestamp[button][0] = timestamp;
    } else if(action == SDL_RELEASED) {
        if(GAMEPAD_HISTORY >= 2) {
            memmove(
                    controller->button_released_timestamp[button]+1, 
                    controller->button_released_timestamp[button],
                    sizeof(Uint32) * (GAMEPAD_HISTORY - 1));
        }
        controller->button_released_timestamp[button][0] = timestamp;
    }
    return;
}

void gamepad_trydo_key(gamepad* controller, SDL_Scancode key, Uint8 action, Uint32 timestamp) {
    if(!controller) return;
    for(int i = 0; i < 16; i++) {
        if(controller->key_buttons[i] == key) {
            gamepad_trydo_button(controller, controller->joystick_id, i, action, timestamp);
            break;
        }
    }
    return;
}

void gamepad_trydo_axis(gamepad* controller, SDL_JoystickID joystick_id, Uint8 axis, Sint16 value, Uint32 timestamp) {
    if(!controller) return;
    if(controller->joystick_id != joystick_id) return;
    if(axis >= 7) return;

    if(GAMEPAD_HISTORY >= 2) {
        memmove(
                controller->axis_timestamp[axis]+1,
                controller->axis_timestamp[axis],
                sizeof(Uint32) * (GAMEPAD_HISTORY - 1));
        memmove(
                controller->axis_state[axis]+1,
                controller->axis_state[axis],
                sizeof(Sint16) * (GAMEPAD_HISTORY - 1));
    }
    controller->axis_timestamp[axis][0] = timestamp;
    controller->axis_state[axis][0] = value;
    
}


