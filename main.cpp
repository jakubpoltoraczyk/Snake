/* Gra "Snake" wersja 1.0 demo */

#include "menu.h"
#include "color_menu.h"
#include "info_menu.h"
#include "snake.h"

int main()
{
    initscr();
    keypad(stdscr,TRUE);
    noecho();
    curs_set(0);
    start_color();
    Menu main_menu("menu_dir/main_menu.txt"), opt_menu("menu_dir/optional_menu.txt");
    Color_menu speed_menu("menu_dir/speed_menu.txt"), map_menu("menu_dir/map_menu.txt"), lang_menu("menu_dir/lang_menu.txt");
    Info_menu rules_menu("menu_dir/rules_menu.txt"), author_menu("menu_dir/author_menu.txt");
    Snake snake;
    int option, speed;
    do
    {
        main_menu.show();
        option = main_menu.choose_option(getch());
        speed = snake.get_game_speed();
        switch(option)
        {
            case 2:
            snake.show();
            option = getch();
            snake.move(option);
            nodelay(stdscr,TRUE);
            do
            {
                snake.show();
                switch(getch())
                {
                    case KEY_UP:
                        option = snake.move(KEY_UP); break;
                    case KEY_DOWN:
                        option = snake.move(KEY_DOWN); break;
                    case KEY_LEFT:
                        option = snake.move(KEY_LEFT); break;
                    case KEY_RIGHT:
                        option = snake.move(KEY_RIGHT); break;
                    case 'e':
                        option = snake.move('e'); break;
                    default:
                        option = snake.move(option);
                }
                napms(speed);
            }while(option!='e'); option = 0;
            nodelay(stdscr,FALSE); break;
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
                        if(option>=3&&option<=5)
                            snake.change_game_speed(Snake::Game_speed(option));
                    }while(option!=1); option = 0; break;
                    case 4:
                    do
                    {
                        map_menu.show();
                        option = map_menu.choose_option(getch());
                        if(option>=3&&option<=5)
                            snake.change_map_size(Snake::Map_size(option));
                    }while(option!=1); option = 0; break;
                    case 5:
                    do
                    {
                        lang_menu.show();
                        option = lang_menu.choose_option(getch());
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