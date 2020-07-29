#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>
#include <vector>

class Snake
{
    private:
        int lines, columns; 
        int x_size, y_size, x1, x2, y1, y2;
        std::vector<std::vector<int>> tab;
        int look_for_tail()const;
        void move_tail(int c);
        int next_step(int c)const;
    public:
        Snake(int map_size);
        void show()const;
        int move(int c);
};

#endif // SNAKE_H