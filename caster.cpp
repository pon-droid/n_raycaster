#include "caster.h"

const int Caster::MAP[MAP_W][MAP_H] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  };


Caster::Caster()
{
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow("Sigma Raycaster",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
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


void Caster::cast_rays()
{
    for(int x = 0; x < SCREEN_W; x++)
    {
        double cam_x = 2 * x / double(SCREEN_W) - 1; //Right of screen is 1, middle 0, left -1
        double rayD_x = dir_x + plane_x * cam_x;
        double rayD_y = dir_y + plane_y * cam_x;

        //Position within array

        int map_x = int(px);
        int map_y = int(py);

        //Distance to next x or y intercept from current pos

        double sdist_x;
        double sdist_y;

        //Length of ray from one x to next x. same with y
        double delta_dx = (rayD_x == 0) ? 1e30 : std::abs(1 / rayD_x);
        double delta_dy = (rayD_y == 0) ? 1e30 : std::abs(1 / rayD_y);

        //Direction i.e. -1 or 1
        int step_x;
        int step_y;

        int hit = 0;
        int side; //X hit or Y hit?

        //Step and intial intercept distance

        if(rayD_x < 0)
        {
            step_x = -1;
            sdist_x = (px - map_x) * delta_dx;
        }
        else
        {
            step_x = 1;
            sdist_x = (map_x + 1.0 - px) * delta_dx;
        }
        if(rayD_y < 0)
        {
            step_y = -1;
            sdist_y = (py - map_y) * delta_dy;
        }
        else
        {
            step_y = 1;
            sdist_y = (map_y + 1.0 - py) * delta_dy;
        }

        //DDA time

        while (hit == 0)
        {
            //jump to next square, x dir or y dir
            if (sdist_x < sdist_y)
            {
                sdist_x += delta_dx;
                map_x += step_x;
                side = 0;
            }
            else
            {
                sdist_y += delta_dy;
                map_y += step_y;
                side = 1;
            }
            //HIT
            if (MAP[map_x][map_y] > 0) hit = 1;
        }

        //Calculate distance from camera plane instead of position, perpindicular.
        //Removes distortion

        double p_wallD;

        if(side == 0)
        {

            p_wallD = (sdist_x - delta_dx);

        }
        else
        {
            p_wallD = (sdist_y - delta_dy);
        }

        //Line height
        int l_height = (int)(SCREEN_H / p_wallD);

        //Find lowest and highest pixel for current column
        int d_start = -l_height / 2 + SCREEN_H / 2;
        if(d_start < 0) d_start = 0;
        int d_end = l_height / 2 + SCREEN_H / 2;
        if(d_end >= SCREEN_H) d_end = SCREEN_H - 1;

        switch(MAP[map_x][map_y])
        {
        case 1: SDL_SetRenderDrawColor(renderer,255,0,0,255); break;
        case 2: SDL_SetRenderDrawColor(renderer,0,255,0,255); break;
        case 3: SDL_SetRenderDrawColor(renderer,0,0,255,255); break;
        case 4: SDL_SetRenderDrawColor(renderer,255,255,255,255); break;
        default: SDL_SetRenderDrawColor(renderer,255,255,0,255); break;
        }

        SDL_RenderDrawLine(renderer, x, d_start, x, d_end);

    }

    p_del = del;
    del = SDL_GetTicks();

    double interval = (del - p_del) / 1000.0;

    m_speed = interval * 5.0;
    r_speed = interval * 3.0;
}

void Caster::player()
{
    const Uint8 *keys = SDL_GetKeyboardState( NULL );

    if(keys[SDL_SCANCODE_UP]){
        if(MAP[int(px + dir_x * m_speed)][int(py)] == false) px += dir_x * m_speed;
        if(MAP[int(px)][int(py + dir_y * m_speed)] == false) py += dir_y * m_speed;
    }
    if(keys[SDL_SCANCODE_DOWN]){
        if(MAP[int(px - dir_x * m_speed)][int(py)] == false) px -= dir_x * m_speed;
        if(MAP[int(px)][int(py - dir_y * m_speed)] == false) py -= dir_y * m_speed;
    }
    if(keys[SDL_SCANCODE_RIGHT]){
        double pre_dir_x = dir_x;
        dir_x = dir_x * cos(-r_speed) - dir_y * sin(-r_speed);
        dir_y = pre_dir_x * sin(-r_speed) + dir_y * cos(-r_speed);
        double pre_plane_x = plane_x;
        plane_x = plane_x * cos(-r_speed) - plane_y * sin(-r_speed);
        plane_y = pre_plane_x * sin(-r_speed) + plane_y * cos(-r_speed);
    }
    if(keys[SDL_SCANCODE_LEFT]){
        double pre_dir_x = dir_x;
        dir_x = dir_x * cos(r_speed) - dir_y * sin(r_speed);
        dir_y = pre_dir_x * sin(r_speed) + dir_y * cos(r_speed);
        double pre_plane_x = plane_x;
        plane_x = plane_x * cos(r_speed) - plane_y * sin(r_speed);
        plane_y = pre_plane_x * sin(r_speed) + plane_y * cos(r_speed);
    }
}
