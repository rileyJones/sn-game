#ifndef ALERT_H
#define ALERT_H

extern SDL_bool alert_active;
//extern background_data alert_background;

void alert_init(SDL_Renderer* renderer);
void alert_quit();
void alert(char* text);

#endif
