#include "menu.h"
#include "color_menu.h"
#include "info_menu.h"

int main()
{
    initscr();
    keypad(stdscr,TRUE);
    noecho();
    curs_set(0);
    start_color();
    Menu main_menu("menu_dir/main_menu.txt"), opt_menu("menu_dir/optional_menu.txt");
    Color_menu speed_menu("menu_dir/speed_menu.txt"), map_menu("menu_dir/map_menu.txt");
    Info_menu rules_menu("menu_dir/rules_menu.txt"), author_menu("menu_dir/author_menu.txt");
    int option;
    do
    {
        main_menu.show();
        option = main_menu.choose_option(getch());
        switch(option)
        {
            case 2:
                break;
            case 3:
            do
            {
                rules_menu.show();
                option = rules_menu.choose_option(getch());
            }while(option!=1); option = 0; break;
            case 4:
            do
            {
                opt_menu.show();
                option = opt_menu.choose_option(getch());
                switch(option)
                {
                    case 3:
                    do
                    {
                        speed_menu.show();
                        option = speed_menu.choose_option(getch());
                    }while(option!=1); option = 0; break;
                    case 4:
                    do
                    {
                        map_menu.show();
                        option = map_menu.choose_option(getch());
                    }while(option!=1); option = 0; break;
                }
            }while(option!=1); option = 0; break;
            case 5:
            do
            {
                author_menu.show();
                option = author_menu.choose_option(getch());
            }while(option!=1); option = 0; break;
        }
    }while(option!=1);
    endwin();
    return 0;
}