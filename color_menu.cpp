#include "color_menu.h"

void Color_menu::show()const
{
    clear();
    refresh();
    init_pair(1,COLOR_RED,COLOR_BLACK); // czerwony - brak wybranej opcji
    init_pair(2,COLOR_GREEN,COLOR_BLACK); // zielony - wybrana opcja
    for(int i=0;i<name_tab[lang].size();++i)
    {
        if(i<=1||i==name_tab[lang].size()-1)
            mvprintw(lines/2+i,columns/2-name_tab[lang][i].size()/2,name_tab[lang][i].data());
        else
        {
            if(i==extra_number)
            {
                attron(COLOR_PAIR(2));
                mvprintw(lines/2+i,columns/2-name_tab[lang][i].size()/2,name_tab[lang][i].data());
                attroff(COLOR_PAIR(2));
            }
            else
            {
                attron(COLOR_PAIR(1));
                attron(A_DIM);
                mvprintw(lines/2+i,columns/2-name_tab[lang][i].size()/2,name_tab[lang][i].data());
                attroff(COLOR_PAIR(1));
                attroff(A_DIM); 
            }
        }
        if(i==act_num)
        {
            attron(A_STANDOUT);
            mvprintw(lines/2+i,columns/2-name_tab[lang][i].size()/2,name_tab[lang][i].data());
            attroff(A_STANDOUT);    
        }
    }
    draw_frame();
}

int Color_menu::choose_option(int c)
{
    if(c==10)
    {
        if(act_num!=name_tab[lang].size()-1)
            extra_number=act_num;
        if(opt_tab[0]==9)
            Menu::change_language(opt_tab[extra_number]);
        return opt_tab[act_num];
    }
    if(c==KEY_DOWN||c==KEY_UP)
        change_actual(c);
    return 0;
}