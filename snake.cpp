#include "snake.h"

Snake::Snake(int map_size): tab(60)
{
    switch(map_size)
    {
        case 1:
        y_size = 40; 
        x_size = y_size/2; break;
        case 2:
        y_size = 50;
        x_size = y_size/2; break;
        case 3:
        y_size = 60; 
        x_size = y_size/2; break;
    }
    for(int i=0;i<x_size;++i)
        for(int j=0;j<y_size;++j)
        {
            if((i==0||i==x_size-1)&&(j==0||j==y_size-1))
                tab[i].push_back(5);
            else
            {
                if((i==0||i==x_size-1)&&(j!=0||j!=y_size-1))
                    tab[i].push_back(3);
                if((i!=0||i!=x_size-1)&&(j==0||j==y_size-1))
                    tab[i].push_back(4);
                if(i!=0&&i!=x_size-1&&j!=0&&j!=y_size-1)
                    tab[i].push_back(0);
            }
        }
    x1 = x2 = x_size/2;
    y1 = y_size/2;
    y2 = y1 + 2;
    tab[x1][y1] = 1;
    tab[x1][y1+1] = tab[x1][y2] = 2; 
    getmaxyx(stdscr,lines,columns);
    lines-=x_size;
    columns-=y_size;
}

void Snake::show()const
{
    clear();
    refresh();
    for(int i=0;i<x_size;++i)
        for(int j=0;j<y_size;++j)
        {
            switch(tab[i][j])
            {
                case 0: 
                mvprintw(lines/2+i,columns/2+j," "); break;
                case 1: 
                mvprintw(lines/2+i,columns/2+j,"o"); break;
                case 2: 
                mvprintw(lines/2+i,columns/2+j,"--"); break;
                case 3:
                mvhline(lines/2+i,columns/2+j,ACS_HLINE,1); break;
                case 4:
                mvvline(lines/2+i,columns/2+j,ACS_VLINE,1); break;
                case 5:
                if(i==0&&j==0) 
                    mvhline(lines/2+i,columns/2+j,ACS_ULCORNER,1);
                if(i==0&&j==y_size-1) 
                    mvhline(lines/2+i,columns/2+j,ACS_URCORNER,1);
                if(i==x_size-1&&j==0) 
                    mvhline(lines/2+i,columns/2+j,ACS_LLCORNER,1);
                if(i==x_size-1&&j==y_size-1) 
                    mvhline(lines/2+i,columns/2+j,ACS_LRCORNER,1);
                break;
            }
        }
}

int Snake::move(int c)
{
    switch(c)
    {
        case KEY_UP:
        tab[x1][y1] = 2;
        tab[--x1][y1] = 1;
        move_tail(look_for_tail()); break;
        case KEY_DOWN:
        tab[x1][y1] = 2;
        tab[++x1][y1] = 1;
        move_tail(look_for_tail()); break;
        case KEY_LEFT:
        tab[x1][y1] = 2;
        tab[x1][--y1] = 1;
        move_tail(look_for_tail()); break;
        case KEY_RIGHT:
        tab[x1][y1] = 2;
        tab[x1][++y1] = 1;
        move_tail(look_for_tail()); break;
    }
    return c;
}

int Snake::look_for_tail()const
{
    if(tab[x2-1][y2]==2)
        return KEY_UP;
    if(tab[x2+1][y2]==2)
        return KEY_DOWN;
    if(tab[x2][y2-1]==2)
        return KEY_LEFT;
    if(tab[x2][y2+1]==2)
        return KEY_RIGHT;
    return 0;  
}

void Snake::move_tail(int c)
{
    switch(c)
    {
        case KEY_UP:
        tab[x2][y2] = 0;
        tab[--x2][y2] = 2; break;
        case KEY_DOWN:
        tab[x2][y2] = 0;
        tab[++x2][y2] = 2; break;
        case KEY_LEFT:
        tab[x2][y2] = 0;
        tab[x2][--y2] = 2; break;
        case KEY_RIGHT:
        tab[x2][y2] = 0;
        tab[x2][++y2] = 2; break;
    } 
}