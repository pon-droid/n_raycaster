#include "caster.h"
#include <iostream>

const int Caster::map[GRID_A] = {
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,1,0,0,0,1,
  1,0,0,1,0,1,0,1,
  1,0,0,1,0,0,0,1,
  1,1,1,1,1,1,1,1,
 };

Caster::Caster()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("WIP RAYCASTER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

}

bool Caster::quit_event()
{

SDL_Event event;

while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
        return false;
    }
}
        return true;

}


void Caster::clr_scrn()
{
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);

}

void Caster::sdl_present()
{
    SDL_RenderPresent(renderer);


}

void Caster::render_map()
{
    SDL_SetRenderDrawColor(renderer,178,190,181,255);
    rect.w = GRID_S;
    rect.h = GRID_S;
    for(int y = 0; y < GRID_H; y++){
        rect.y = 0 + (y * GRID_S);
        for(int x = 0; x < GRID_W; x++){
            rect.x = 0 + (x * GRID_S);
            if(map[y*GRID_W+x] == 1){
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
}

void Caster::handle_pl(){

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    const Uint8* keys = SDL_GetKeyboardState( NULL );

    if( keys[SDL_SCANCODE_UP]){
        pl.x += lx;
        pl.y += ly;
    }
    if( keys[SDL_SCANCODE_DOWN]){
        pl.x -= lx;
        pl.y -= ly;
    }
    if( keys[SDL_SCANCODE_LEFT]){
        pl.x -= 4;
        pa -= .1;
        if(pa < 0){
            pa = 2*M_PI;
        }
        lx=cos(pa) * 2;
        ly=sin(pa) * 2;

    }
    if( keys[SDL_SCANCODE_RIGHT]){
        pl.x += 4;
        pa += .1;
        if(pa > 2*M_PI){
            pa = 0;
        }
        lx=cos(pa) * 2;
        ly=sin(pa) * 2;
    }

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderFillRect(renderer,&pl);
    SDL_RenderDrawLine(renderer,pl.x,pl.y,pl.x+lx*5,pl.y+ly*5);


}


void Caster::cast_rays(){
    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    double ray_a = pa - 30 * (M_PI / 180);
    if(ray_a < 0){
        ray_a = 2 * M_PI;
    }
    if(ray_a > 2 * M_PI){
        ray_a = 0;
    }

    double ray_x;
    double ray_y;
    for(int r = 0; r < 600; r+= 10){
        bool w_hit = false;
        ray_x = pl.x;
        ray_y = pl.y;

        do{
            ray_x += cos(ray_a);
            ray_y += sin(ray_a);

            int indeX = ray_x / GRID_S;
            int indeY = ray_y / GRID_S;

            if(indeX < GRID_W && indeY < GRID_H && Caster::map[indeY*GRID_W+indeX] == 1){
                w_hit = true;
            }

        }while(!w_hit);

        SDL_RenderDrawLine(renderer,pl.x,pl.y,ray_x,ray_y);

        double w_dist = sqrt((ray_x - pl.x) * (ray_x - pl.x) + (ray_y - pl.y) * (ray_y - pl.y));

        double a_diff = pa - ray_a;
        if(a_diff < 0) a_diff += 2 * M_PI;
        if(a_diff > 0) a_diff -= 2 * M_PI;

        w_dist = w_dist * cos(a_diff);


        double l_height = (GRID_S * SCREEN_H) / w_dist;
        if(l_height > SCREEN_H) l_height = SCREEN_H;

        int x_o = ((SCREEN_H / 2) - l_height / 2) + 200;
        int y_o = (GRID_H * GRID_S) + 25;
        SDL_SetRenderDrawColor(renderer,0,255,0,255);

        for(int i = 0; i < 10; i++){
            SDL_RenderDrawLine(renderer, r + i + x_o, y_o, r + i + x_o, l_height + y_o);
        }
        ray_a += M_PI / 180;

    }



}


void Caster::free(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

