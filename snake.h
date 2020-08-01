#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "info_menu.h"

class Snake
{
    public:
        enum Map_size {small = 3, medium = 4, big = 5};
        explicit Snake(const Map_size & ms = medium);
        void show()const;
        int move(int c);
        void change_map_size(const Map_size & ms);
    private:
        const static int max_size = 40;
        int lines, columns; 
        int x_size, y_size, x1, x2, y1, y2;
        std::vector<std::vector<int>> tab;
        int added_food, counter, points;
        enum Map_size map_size;
        Info_menu result_message;
        int look_for_tail()const;
        void move_tail(int c);
        int next_step(int c)const;
        void add_element();
        void reset();
        void show_result();
        int get_result_points();
};

#endif // SNAKE_H