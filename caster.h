#ifndef CASTER_H
#define CASTER_H

#include <SDL.h>
#include <math.h>
#include <iostream>

class Caster
{
public:
    //Loop
    bool quit_event();
    void sdl_present();
    void clr_scrn();
    //Core
    Caster();
    const double deg = (M_PI / 180);

    //SCREEN
    SDL_Window *window;
    SDL_Renderer *renderer;
    const int PLANE_W = 320;
    const int PLANE_H = 200;

    const int plane_d = (PLANE_W/2) / tan(30 * deg);
    //MAP
    const int S_MAP = 64;
    const int MAP_W = 8;
    const int MAP_H = 8;
    const int MAP_A = MAP_W * MAP_H;
    static const int MAP[64];
    SDL_Rect WALL;
    void draw_map();
    //Player
    SDL_Rect player = {160,100,32,32};
    float delta_x = 1;
    float delta_y = 1;
    float v_angle = 0;
    void h_player();
    //Ray time
    void cast_rays();

};

#endif // CASTER_H
