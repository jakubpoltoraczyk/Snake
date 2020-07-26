#ifndef INFO_MENU_H 
#define INFO_MENU_H 

#include "menu.h"

class Info_menu: public Menu
{
    public:
        Info_menu(const std::string & filename): Menu(filename) {}
        virtual int choose_option(int c)override;
};

#endif // INFO_MENU_H 