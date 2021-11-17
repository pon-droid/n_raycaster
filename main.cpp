#include <SDL.h>
#include "caster.h"


int main()
{
    Caster caster;

    while(true){
        caster.clr_scrn();
        caster.cast_rays();
        caster.player();
        caster.sdl_present();
        if(caster.quit_event() == true){
            break;
        }
    }

    return 0;
}
