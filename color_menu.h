/* Klasa reprezentujaca proste kolorowe menu gry wykorzystujace biblioteke ncurses. Oprocz mozliwosci dziedziczonych po klasie 'Menu',
   klasa ta udostepnia kolorowanie wybranych przez uzytkownika opcji na zielono, niewybranych na czerowno oraz zmiane aktualnie wybranej opcji */

#ifndef COLOR_MENU_H
#define COLOR_MENU_H

#include "menu.h"

class Color_menu: public Menu // dziedziczy po podstawowym menu
{
    private:
        int extra_number; // przechowuje obecnie wybrana opcje przez uzytkownika
    public:
        Color_menu(const std::string & filename): Menu(filename), extra_number(2) {}
        virtual int choose_option(int c) override; // dodatkowe aktualizowanie extra_number
        virtual void show()const override; // dodanie kolorkow
};

#endif // COLOR_MENU_H