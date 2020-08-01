#include "info_menu.h"

Info_menu::Info_menu(const std::string & filename): Menu(filename), lngst_name(number_of_languages)
{
    for(int i=0;i<number_of_languages;++i)
        lngst_name[i]=0;
    for(int i=0;i<number_of_languages;++i)
        for(int j=0;j<name_tab[i].size();++j)
            if(lngst_name[i]<name_tab[i][j].size())
                lngst_name[i]=name_tab[i][j].size();
}

void Info_menu::draw_frame()const
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

int Info_menu::choose_option(int c)
{
    if(c==10)
        return opt_tab[act_num];
    return 0;
}

void Info_menu::operator+=(const std::string & mes)
{
    int n = name_tab[lang][name_tab[lang].size()-1].size();
    name_tab[lang][name_tab[lang].size()-1][n-1] = ' ';
    name_tab[lang][name_tab[lang].size()-1]+=mes;
    lngst_name[lang]+=mes.size()+1;
}