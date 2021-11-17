#ifndef CASTER_H
#define CASTER_H

#include<SDL.h>

class Caster
{
public:
    Caster();
    //WINDOW
    SDL_Window *window;
    SDL_Renderer *renderer;
    static const int SCREEN_W = 640;
    static const int SCREEN_H = 480;

    void clr_scrn();
    void sdl_present();
    bool quit_event();

    //MAP
    static const int MAP_W = 24;
    static const int MAP_H = 24;
    static const int MAP[MAP_W][MAP_H];
    //Rays
    double px = 22;
    double py = 12;

    double dir_x = -1;
    double dir_y = 0;

    double plane_x = 0;
    double plane_y = .66; // 66 Degrees FOV

    void cast_rays();

    //Interval sync
    double del = 0;
    double p_del = 0;

    double m_speed;
    double r_speed;

    //Movement
    void player();


};

#endif // CASTER_H
