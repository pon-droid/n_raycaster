#ifndef CASTER_H
#define CASTER_H

#include <SDL.h>
#include <math.h>
class Caster
{

public:
    static const unsigned char GRID_H = 8;
    static const unsigned char GRID_W = 8;
    static const int GRID_S = 75;
    static const  int SCREEN_H = 800;
    static const  int SCREEN_W = 1400;
    static const unsigned char GRID_A = GRID_H*GRID_W;

    static const int map[GRID_A];


private:
    SDL_Window *window;


    SDL_Renderer *renderer;


public:
    Caster();
    bool quit_event();
    void clr_scrn();
    void sdl_present();

    //Map
    SDL_Rect rect;
    void render_map();
    //Player
    SDL_Rect pl = {75,75,20,20};
    float lx = 2;
    float ly = 2;
    float pa = 0;
    void handle_pl();
    //Rays
    void cast_rays();

    //Cleanup
    void free();


};

#endif // CASTER_H
