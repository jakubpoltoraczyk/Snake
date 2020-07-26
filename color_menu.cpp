#include "color_menu.h"

void Color_menu::show()const
{
    clear();
    refresh();
    init_pair(1,COLOR_RED,COLOR_BLACK); // czerwony - brak wybranej opcji
    init_pair(2,COLOR_GREEN,COLOR_BLACK); // zielony - wybrana opcja
    for(int i=0;i<name_tab.size();++i)
    {
        if(i<=1||i==name_tab.size()-1)
            mvprintw(lin/2+i,col/2-name_tab[i].size()/2,name_tab[i].data());
        else
        {
            if(i==extra_number)
            {
                attron(COLOR_PAIR(2));
                mvprintw(lin/2+i,col/2-name_tab[i].size()/2,name_tab[i].data());
                attroff(COLOR_PAIR(2));
            }
            else
            {
                attron(COLOR_PAIR(1));
                attron(A_DIM);
                mvprintw(lin/2+i,col/2-name_tab[i].size()/2,name_tab[i].data());
                attroff(COLOR_PAIR(1));
                attroff(A_DIM); 
            }
        }
        if(i==act_num)
        {
            attron(A_STANDOUT);
            mvprintw(lin/2+i,col/2-name_tab[i].size()/2,name_tab[i].data());
            attroff(A_STANDOUT);    
        }
    }
    draw_frame();
}

int Color_menu::choose_option(int c)
{
    if(c==10)
    {
        if(act_num>1&&act_num!=name_tab.size()-1)
            extra_number=act_num;
        return opt_tab[act_num];
    }
    if(c==KEY_DOWN||c==KEY_UP)
        change_actual(c);
    return 0;
}