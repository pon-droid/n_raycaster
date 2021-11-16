#include "caster.h"


int main()
{
    Caster caster;
    while(true){
        caster.clr_scrn();
        caster.draw_map();
        caster.h_player();
        caster.cast_rays();
        caster.sdl_present();
        if(caster.quit_event() == true){
            break;
        }
    }
    return 0;
}
