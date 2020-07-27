#include "menu.h"

language Menu::lang = POL;

void Menu::change_lang(int c)
{
    switch(c)
    {
        case 3:
        lang = POL; break;
        case 4:
        lang = ENG; break;
    }
}

Menu::Menu(const std::string & filename): act_num(2), lines(), columns(), name_tab(2), lngst_name(2)
{
    std::ifstream file;
    std::string name;
    int opt;
    file.open(filename);
    for(int i=0;!file.eof();++i)
    {
        if(file.peek()=='~')
        {
            file.get();
            lang=language(lang+1);
        }
        file >> opt;
        opt_tab.push_back(opt);
        getline(file,name);
        name+="\n";
        name_tab[lang].push_back(name);
        if(name.size()>lngst_name[lang])
            lngst_name[lang]=name.size();
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
    mvhline(lines/2-2,columns/2-lngst_name[lang]/2-3,ACS_HLINE,lngst_name[lang]+5);
    mvhline(lines/2+name_tab[lang].size()+1,columns/2-lngst_name[lang]/2-3,ACS_HLINE,lngst_name[lang]+5);
    mvvline(lines/2-1,columns/2-lngst_name[lang]/2-4,ACS_VLINE,name_tab[lang].size()+2);
    mvvline(lines/2-1,columns/2+lngst_name[lang]/2+2,ACS_VLINE,name_tab[lang].size()+2);
    mvhline(lines/2-2,columns/2-lngst_name[lang]/2-4,ACS_ULCORNER,1);
    mvhline(lines/2+name_tab[lang].size()+1,columns/2-lngst_name[lang]/2-4,ACS_LLCORNER,1);
    mvvline(lines/2-2,columns/2+lngst_name[lang]/2+2,ACS_URCORNER,1);
    mvvline(lines/2+name_tab[lang].size()+1,columns/2+lngst_name[lang]/2+2,ACS_LRCORNER,1);
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