#ifndef GAMEPAD_H
#define GAMEPAD_H
#define GAMEPAD_HISTORY 2

typedef struct {
    // -1 = keyboard only controller
    SDL_JoystickID joystick_id;
    
    // A B X Y 
    // Back Guide Start 
    // LStick RStick LBumper RBumper 
    // Up Down Left Right
    // MISC1
    Uint32 button_pressed_timestamp[16][GAMEPAD_HISTORY];
    Uint32 button_released_timestamp[16][GAMEPAD_HISTORY];
    Uint8 button_state[3][16];
    
    SDL_Scancode key_buttons[16];

    //LX LY
    //RX RY
    //LT RT
    Uint32 axis_timestamp[7][GAMEPAD_HISTORY];
    Sint16 axis_state[7][GAMEPAD_HISTORY];

} gamepad;

void gamepad_create(gamepad* controller, SDL_JoystickID joystick_id);

void gamepad_set_key_button(
        gamepad* controller, 
        SDL_Scancode scancode, 
        Uint8 button);

SDL_bool gamepad_button_pressed(gamepad* controller, Uint8 button);

SDL_bool gamepad_button_held(gamepad* controller, Uint8 button);

SDL_bool gamepad_button_released(gamepad* controller, Uint8 button);

SDL_bool gamepad_button_repressed(gamepad* controller, Uint8 button, Uint32 delta);

void gamepad_update(gamepad* controller);

void gamepad_trydo_button(gamepad* controller, SDL_JoystickID joystick_id, Uint8 button, Uint8 action, Uint32 timestamp);

void gamepad_trydo_key(gamepad* controller, SDL_Scancode key, Uint8 action, Uint32 timestamp);

void gamepad_trydo_axis(gamepad* controller, SDL_JoystickID joystick_id, Uint8 axis, Sint16 value, Uint32 timestamp);

#endif
