#include "menu.h"

Language Menu::lang = POL;

void Menu::change_language(int c)
{
    switch(c)
    {
        case 3:
        lang = ENG; break;
        case 4:
        lang = POL; break;
    }
}

Menu::Menu(const std::string & filename): act_num(2), lines(), columns(), name_tab(number_of_languages)
{
    std::ifstream file;
    std::string name;
    int opt;
    file.open(filename);
    while(!file.eof())
    {
        if(file.peek()=='~')
        {
            file.get();
            lang=Language(lang+1);
        }
        file >> opt;
        opt_tab.push_back(opt);
        getline(file,name);
        name+="\n";
        name_tab[lang].push_back(name);
    }
    getmaxyx(stdscr,lines,columns);
    lines-=2*name_tab.size(); // kwestia estetyki
    lang=POL;
    file.close();
}

void Menu::change_actual(int c)
{
    if(c==KEY_UP&&act_num>2)
        --act_num;
    if(c==KEY_DOWN&&act_num<name_tab[lang].size()-1)
        ++act_num;
}

void Menu::draw_frame()const
{
    mvhline(lines/2-2,columns/2-12,ACS_HLINE,22);
    mvhline(lines/2+8,columns/2-12,ACS_HLINE,22);
    mvvline(lines/2-1,columns/2-12,ACS_VLINE,9);
    mvvline(lines/2-1,columns/2+10,ACS_VLINE,9);
    mvhline(lines/2-2,columns/2-12,ACS_ULCORNER,1);
    mvhline(lines/2+8,columns/2-12,ACS_LLCORNER,1);
    mvvline(lines/2-2,columns/2+10,ACS_URCORNER,1);
    mvvline(lines/2+8,columns/2+10,ACS_LRCORNER,1);
}

void Menu::show()const
{
    clear(); // jedyne miejsca dla odswiezania okna
    refresh();
    for(int i=0;i<name_tab[lang].size();++i)
    {
        if(i==act_num) // podswietlenie tla
        {
            attron(A_STANDOUT);
            mvprintw(lines/2+i,columns/2-name_tab[lang][i].size()/2,name_tab[lang][i].data());
            attroff(A_STANDOUT);
        }
        else // normalna czcionka
            mvprintw(lines/2+i,columns/2-name_tab[lang][i].size()/2,name_tab[lang][i].data());
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