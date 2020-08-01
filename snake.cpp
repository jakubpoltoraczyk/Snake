#include "snake.h"

Snake::Snake(const Map_size & ms): tab(max_size), added_food(), counter(), map_size(ms), result_message("menu_dir/info_snake_result.txt"), points()
{
    srand(time(NULL));
    for(int i=0;i<max_size;++i)
        for(int j=0;j<max_size;++j)
            tab[i].push_back(0);
    change_map_size(map_size);
}

void Snake::show()const
{
    clear();
    refresh();
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    for(int i=0;i<x_size;++i)
        for(int j=0;j<y_size;++j)
        {
            switch(tab[i][j])
            {
                case 0: 
                mvprintw(lines/2+i,columns/2+j," "); break;
                case 1: 
                attron(COLOR_PAIR(1));
                mvprintw(lines/2+i,columns/2+j,"o");
                attroff(COLOR_PAIR(1)); break;
                case 2: 
                attron(COLOR_PAIR(1));
                mvprintw(lines/2+i,columns/2+j,"-");
                attroff(COLOR_PAIR(1)); break;
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
                case 6:
                attron(COLOR_PAIR(2));
                mvprintw(lines/2+i,columns/2+j,"+");
                attroff(COLOR_PAIR(2)); break;
                case 7:
                attron(COLOR_PAIR(3));
                mvprintw(lines/2+i,columns/2+j,"@");
                attroff(COLOR_PAIR(3)); break;
                case 8:
                attron(COLOR_PAIR(4));
                mvprintw(lines/2+i,columns/2+j,"$");
                attroff(COLOR_PAIR(4)); break;

            }
        }
}

int Snake::move(int c)
{
    int next_element;
    ++counter;
    add_element();
    switch(c)
    {
        case KEY_UP:
        next_element = next_step(KEY_UP);
        if(next_element<2||next_element>5)
        {
            if(next_element==7)
                points+=200;
            if(next_element==8)
                points+=500;
            if(next_element!=6)
                move_tail(look_for_tail());
            else
                ++added_food;
            tab[x1][y1] = 2;
            tab[--x1][y1] = 1;
            return c;
        }
        show_result();
        return 'e';
        case KEY_DOWN:
        next_element = next_step(KEY_DOWN);
        if(next_element<2||next_element>5)
        {
            if(next_element==7)
                points+=200;
            if(next_element==8)
                points+=500;
            if(next_element!=6)
                move_tail(look_for_tail());
            else
                ++added_food;
            tab[x1][y1] = 2;
            tab[++x1][y1] = 1;  
            return c;
        }
        show_result();    
        return 'e';
        case KEY_LEFT:
        next_element = next_step(KEY_LEFT);
        if(next_element<2||next_element>5)
        {
            if(next_element==7)
                points+=200;
            if(next_element==8)
                points+=500;
            if(next_element!=6)
                move_tail(look_for_tail());
            else
                ++added_food;
            tab[x1][y1] = 2;
            tab[x1][--y1] = 1;
            return c;
        }
        show_result();
        return 'e';
        case KEY_RIGHT:
        next_element = next_step(KEY_RIGHT);
        if(next_element<2||next_element>5)
        {
            if(next_element==7)
                points+=200;
            if(next_element==8)
                points+=500;
            if(next_element!=6)
                move_tail(look_for_tail());
            else
                ++added_food;
            tab[x1][y1] = 2;
            tab[x1][++y1] = 1;
            return c;
        }
        show_result();
        return 'e';
        case 'e':
        show_result();
        return 'e';
    }
    return c;
}

void Snake::change_map_size(const Map_size & ms)
{
    map_size = ms;
    switch(map_size)
    {
        case small:
        y_size = max_size*0.6; 
        x_size = y_size/2; break;
        case medium:
        y_size = max_size*0.8;
        x_size = y_size/2; break;
        case big:
        y_size = max_size; 
        x_size = y_size/2; break;
    }
    for(int i=0;i<x_size;++i)
        for(int j=0;j<y_size;++j)
        {
            if((i==0||i==x_size-1)&&(j==0||j==y_size-1))
                tab[i][j]=5;
            else
            {
                if((i==0||i==x_size-1)&&(j!=0||j!=y_size-1))
                    tab[i][j]=3;
                if((i!=0||i!=x_size-1)&&(j==0||j==y_size-1))
                    tab[i][j]=4;
                if(i!=0&&i!=x_size-1&&j!=0&&j!=y_size-1)
                    tab[i][j]=0;
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

int Snake::look_for_tail()const
{
    int c[2];
    int counter = 0;
    if(tab[x2-1][y2]==2)
        c[counter++] = KEY_UP;
    if(tab[x2+1][y2]==2)
        c[counter++] = KEY_DOWN;
    if(tab[x2][y2-1]==2)
        c[counter++] = KEY_LEFT;
    if(tab[x2][y2+1]==2)
        c[counter++] = KEY_RIGHT;
    if(counter>1)
    {
        if((c[0]==KEY_UP||c[1]==KEY_UP)&&x1>x2+1)
            return KEY_UP;
        if((c[0]==KEY_DOWN||c[1]==KEY_DOWN)&&x1<x2-1)
            return KEY_DOWN;
        if((c[0]==KEY_LEFT||c[1]==KEY_LEFT)&&y1>y2+1)
            return KEY_LEFT;
        if((c[0]==KEY_RIGHT||c[1]==KEY_RIGHT)&&y1<y2-1)
            return KEY_RIGHT;
    }
    else
        return c[0];
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

int Snake::next_step(int c)const
{
    switch(c)
    {
        case KEY_UP:
        return tab[x1-1][y1]; 
        case KEY_DOWN:
        return tab[x1+1][y1];
        case KEY_LEFT:
        return tab[x1][y1-1];
        case KEY_RIGHT:
        return tab[x1][y1+1];
    }
    return 0;
}

void Snake::add_element()
{
    int draw_x_number, draw_y_number, draw_number;
    if(counter%10==0||counter==1)
    {
        do
        {
            draw_x_number = (std::rand()%x_size)+0;
            draw_y_number = (std::rand()%y_size)+0;
        }while(tab[draw_x_number][draw_y_number]!=0);
        draw_number = (std::rand()%100)+1;
        if(draw_number<=75)
            tab[draw_x_number][draw_y_number] = 6;
        if(draw_number>75&draw_number<=90)
            tab[draw_x_number][draw_y_number] = 7;
        if(draw_number>90&&draw_number<=95)
            tab[draw_x_number][draw_y_number] = 8;
    }
}

void Snake::reset()
{
    added_food = counter = 0;
    change_map_size(map_size);
}

void Snake::show_result()
{
    nodelay(stdscr,FALSE);
    Info_menu copy_message = result_message;
    copy_message+=std::to_string(get_result_points());
    copy_message.show();
    while(copy_message.choose_option(getch())!=1);
    nodelay(stdscr,TRUE);
    reset();
}

int Snake::get_result_points()
{
    switch(map_size)
    {
        case small:
        added_food*=3; break;
        case medium:
        added_food*=2; break;
        case big:
        added_food*=1; break;
    }
    return points+added_food*50;
}