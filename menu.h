/* Klasa reprezentujaca proste menu gry wykorzystujace biblioteke ncurses. Umozliwia ona wyswietlenie tekstu menu otoczonego ramka
   na srodku ekranu, podswietlenie aktualnie wybranej pozycji w menu, przesuwanie sie pomiedzy dostepnymi pozycjami i wybor danej opcji */

#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <fstream>
#include <vector>

enum language // typ wyliczeniowy sluzacy do wyboru jezyka menu
{
    POL = 0,
    ENG = 1
};

class Menu
{
    protected:
        int act_num, lines, columns; // 1.aktualnie wybrana pozycja, 2.numer lini na ekranie (wyswietlanie), 3.numer kolumny na ekranie (wyswietlanie)
        std::vector<int> lngst_name; // przechowywanie najdluzszej nazwy w kazdym jezyku
        std::vector<std::vector<std::string>> name_tab; // tabela nazw opcji menu (czytane z pliku)
        std::vector<int> opt_tab; // tabela opcji/dzialan (niewidoczne dla uzytkownika, czytane z pliku np. 0-brak dzialania, 1-wyjscie/powrot, 2-gra, 3 i wiecej-rozne dzialania )
        static language lang; // zmienna do przechowywania jezyka menu
        static void change_lang(int c); // metoda zmieniajaca obecny jezyk
        void change_actual(int c); // metoda zmieniajaca wartosc act_num
        void draw_frame()const; // metoda rysujaca ramke otaczajca menu
    public:
        Menu(const std::string & filename); // podawana nazwa pliku z nazwami i opcjami do odczytu
        virtual ~Menu() {}
        virtual int choose_option(int c); // metoda reagujaca na wybierany znak, okreslajaca dzialanie (zwraca opt_tab)
        virtual void show()const; // metoda wyswietlajaca
};

#endif // MENU_H 