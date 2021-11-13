#include <iostream>
#include "caster.h"

using namespace std;

int main()
{
    Caster blaster;

    while(true){
        blaster.clr_scrn();
        blaster.handle_pl();
        blaster.render_map();
        blaster.cast_rays();
        blaster.sdl_present();
        if(blaster.quit_event() == false){
            break;
        }
    }

    blaster.free();

    return 0;
}
