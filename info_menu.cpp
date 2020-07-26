#include "info_menu.h"

int Info_menu::choose_option(int c)
{
    if(c==10)
        return opt_tab[act_num];
    return 0;
}