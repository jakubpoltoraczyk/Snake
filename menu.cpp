#include "menu.h"

Menu::Menu(const std::string & filename): act_num(2), lngst_name(), lin(), col()
{
    std::ifstream file;
    std::string name;
    int opt;
    file.open(filename);
    for(int i=0;!file.eof();++i)
    {
        file >> opt;
        opt_tab.push_back(opt);
        getline(file,name);
        name+="\n";
        name_tab.push_back(name);
        if(name.size()>lngst_name)
            lngst_name=name.size();
    }
    getmaxyx(stdscr,lin,col);
    lin-=name_tab.size(); // kwestia estetyki
    file.close();
}

void Menu::change_actual(int c)
{
    if(c==KEY_UP&&act_num>2)
        --act_num;
    if(c==KEY_DOWN&&act_num<name_tab.size()-1)
        ++act_num;
}

void Menu::draw_frame()const
{
    mvhline(lin/2-1,col/2-lngst_name/2-2,ACS_HLINE,lngst_name+3);
    mvhline(lin/2+name_tab.size(),col/2-lngst_name/2-2,ACS_HLINE,lngst_name+3);
    mvvline(lin/2,col/2-lngst_name/2-3,ACS_VLINE,name_tab.size());
    mvvline(lin/2,col/2+lngst_name/2+1,ACS_VLINE,name_tab.size());
    mvhline(lin/2-1,col/2-lngst_name/2-3,ACS_ULCORNER,1);
    mvhline(lin/2+name_tab.size(),col/2-lngst_name/2-3,ACS_LLCORNER,1);
    mvvline(lin/2-1,col/2+lngst_name/2+1,ACS_URCORNER,1);
    mvvline(lin/2+name_tab.size(),col/2+lngst_name/2+1,ACS_LRCORNER,1);
}

void Menu::show()const
{
    clear(); // jedyne miejsca dla odswiezania okna
    refresh();
    for(int i=0;i<name_tab.size();++i)
    {
        if(i==act_num) // podswietlenie tla
        {
            attron(A_STANDOUT);
            mvprintw(lin/2+i,col/2-name_tab[i].size()/2,name_tab[i].data());
            attroff(A_STANDOUT);
        }
        else // normalna czcionka
            mvprintw(lin/2+i,col/2-name_tab[i].size()/2,name_tab[i].data());
    }
    draw_frame();
}

int Menu::choose_option(int c)
{
    if(c==10) // 'enter'
        return opt_tab[act_num]; // zwrocenie wybranej opcji
    if(c==KEY_DOWN||c==KEY_UP)
        change_actual(c); // zmiana jedynie aktualnego msc w menu
    return 0;
}