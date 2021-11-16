#include "caster.h"

const int Caster::MAP[64] = {
  1,1,1,1,1,1,1,1,
  1,0,0,0,0,0,0,1,
  1,0,0,1,0,0,0,1,
  1,0,0,1,0,0,0,1,
  1,0,0,1,0,0,0,1,
  1,0,0,1,1,1,0,1,
  1,0,0,1,0,0,0,1,
  1,1,1,1,1,1,1,1,
 };



Caster::Caster()
{


    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Sigma Raycaster",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,PLANE_W,PLANE_H,SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);\
}

bool Caster::quit_event()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return true;
        }
    }
    return false;
}

void Caster::clr_scrn()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
}

void Caster::sdl_present()
{
    SDL_RenderPresent(renderer);
}

void Caster::draw_map()
{
    WALL.h = S_MAP;
    WALL.w = S_MAP;

    for(int y = 0; y < MAP_H; y++){
        WALL.y = 0 + (y * S_MAP);
        for(int x = 0; x < MAP_W; x++){
            WALL.x = 0 + (x * S_MAP);
            if(MAP[y*MAP_W+x] == 1){
                SDL_SetRenderDrawColor(renderer,0,255,0,255);
            } else{
                SDL_SetRenderDrawColor(renderer,255,0,0,255);
            }
            SDL_RenderFillRect(renderer,&WALL);
        }
    }
}

void Caster::h_player()
{
    SDL_SetRenderDrawColor(renderer,0,0,255,255);

    const Uint8 *keys = SDL_GetKeyboardState( NULL );

    if( keys[SDL_SCANCODE_UP]){
        player.x += delta_x;
        player.y += delta_y;
    }
    if( keys[SDL_SCANCODE_DOWN]){
        player.x -= delta_x;
        player.y -= delta_y;
    }
    if( keys[SDL_SCANCODE_LEFT]){
        player.x -= 4;
        v_angle -= .1;
        if( v_angle < 0){
            v_angle = 2 * M_PI;
        }
        delta_x = cos(v_angle) * 2;
        delta_y = sin(v_angle) * 2;
    }
    if( keys[SDL_SCANCODE_RIGHT]){
        player.x += 4;
        v_angle += .1;
        if( v_angle > 2 * M_PI){
            v_angle = 0;
        }
        delta_x = cos(v_angle) * 2;
        delta_y = sin(v_angle) * 2;
    }
    SDL_RenderFillRect(renderer,&player);
    SDL_RenderDrawLine(renderer,player.x,player.y,player.x + delta_x * 5, player.y + delta_y * 5);
}

void Caster::cast_rays()
{
    float ray_a = v_angle - 30 * deg;
    if(ray_a < 0){
        ray_a = 2 * M_PI;
    }
    if(ray_a > 2 * M_PI){
        ray_a = 0;
    }

    double a_y, a_x;

    if(ray_a > M_PI){
        std::cout << "UP" << std::endl;
        a_y = (player.y/S_MAP) * (S_MAP) - 1;
    }
    if(ray_a < M_PI){
        std::cout << "DOWN" << std::endl;
        a_y = (player.y/S_MAP) * (S_MAP) + S_MAP;
    }

    a_x = player.x + (player.y - a_y)/tan(ray_a);
    /*

    double X_int, Y_int;
    X_int = S_MAP/tan(ray_a);

    bool hit = false;
    do{
        int indeX = X_int/S_MAP;
        if(indeX < MAP_A && indeX > 0 && MAP[])
    }
    while(!(hit));
    */
}
