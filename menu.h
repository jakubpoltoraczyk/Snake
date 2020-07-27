/* Klasa reprezentujaca proste menu gry wykorzystujace biblioteke ncurses. Umozliwia ona wyswietlenie tekstu menu otoczonego stala ramka
   na srodku ekranu, podswietlenie aktualnie wybranej pozycji w menu, przesuwanie sie pomiedzy dostepnymi pozycjami i wybor danej opcji */

#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <fstream>
#include <vector>

enum Language // typ wyliczeniowy sluzacy do wyboru jezyka menu
{
    POL = 0,
    ENG = 1
};

class Menu
{
    protected:
        int act_num, lines, columns; // 1.aktualnie wybrana pozycja, 2.numer lini na ekranie (wyswietlanie), 3.numer kolumny na ekranie (wyswietlanie)
        static Language lang; // zmienna do przechowywania jezyka menu
        const static int number_of_languages = 2;
        std::vector<std::vector<std::string>> name_tab; // tabela nazw opcji menu (czytane z pliku)
        std::vector<int> opt_tab; // tabela opcji/dzialan (niewidoczne dla uzytkownika, czytane z pliku np. 0-brak dzialania, 1-wyjscie/powrot, 2-gra, 3 i wiecej-rozne dzialania)
        static void change_language(int c); // metoda zmieniajaca obecny jezyk
        void change_actual(int c); // metoda zmieniajaca wartosc act_num
        virtual void draw_frame()const; // metoda rysujaca ramke otaczajca menu
    public:
        Menu(const std::string & filename); // podawana nazwa pliku z nazwami i opcjami do odczytu
        virtual ~Menu() {}
        virtual int choose_option(int c); // metoda reagujaca na wybierany znak, okreslajaca dzialanie (zwraca opt_tab)
        virtual void show()const; // metoda wyswietlajaca
};

#endif // MENU_H 