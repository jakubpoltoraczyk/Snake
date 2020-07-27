/* Klasa reprezentujaca proste menu informacyjne z wykorzystaniem biblioteki ncurses. Ogranicza ona korzysci wynikajace z dziedziczenia 
   po klasie 'Menu', udostepniajac jedynie opcje powrotu do poprzedniej strony menu. Wyswietla tekst o charakterze informacyjnym w ramce o zmiennej wielkosci */

#ifndef INFO_MENU_H 
#define INFO_MENU_H 

#include "menu.h"

class Info_menu: public Menu
{
    protected:
        std::vector<int> lngst_name;
        virtual void draw_frame()const override;
    public:
        Info_menu(const std::string & filename);
        virtual int choose_option(int c)override;
};

#endif // INFO_MENU_H 