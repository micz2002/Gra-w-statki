#include "..\Statki\Klasy\Plansza\Plansza.h"
#include "..\Statki\Klasy\Statek\Statek.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

/**
* Funkcja otwiera plik z instrukcja, w przypadku braku dostepu do pliku zostaje rzucony wyjatek.
*
* Pobiera dana typu fstream poprzez referencje
* \param[in,out] instrukcja obiekt pliku z instrukcja gry.
* \exception runtime_error brak dostepu do pliku.
*/
void odczytaj_Instrukcje(fstream &instrukcja)
{ 
        instrukcja.open("instrukcja.txt", ios::in);
        if (instrukcja.is_open())
        {
            string linia;
            while (getline(instrukcja, linia))
            {
                cout << linia << endl;
            }
            instrukcja.close();
        }
        else throw runtime_error("Brak dostepu do pliku!");
}

/**
* Funkcja ustawia widocznosc planszy AI w zaleznosci od wyboru gracza.
* 
* Pobiera poprzez referencje wartosc typu int oraz bool.
* \param[in,out] wybor_Widocznosci wybor widocznosci statkow AI.
* \param[in,out] czy_Widoczna widocznosc statkow AI na planszy, ma wartosc true jesli gracz wybral, aby statki AI na planszy byly widoczne, w przeciwnym wypadku false.
*/
void ustaw_Widocznosc(int &wybor_Widocznosci, bool &czy_Widoczna)
{
    do
    {
        cout << "Wcisnij 1 lub 2" << endl;
        while (!(cin >> wybor_Widocznosci)) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Nie wprowadzono liczby" << endl;
        }
    } while (wybor_Widocznosci != 1 && wybor_Widocznosci != 2);
    if (wybor_Widocznosci == 1)
        czy_Widoczna = true;
    else czy_Widoczna = false;
}

/**
* Rozpoczecie gry. Rozmieszczenie statkow przez gracza oraz AI.
* 
* * Pobiera dwie dane typu Plansza poprzez referencje oraz wartosc typu bool.
* \param[in,out] p1 obiekt gracza.
* \param[in,out] ai obiekt AI.
* \param[in,out] czy_Widoczna widocznosc statkow AI na planszy, ma wartosc true jesli gracz wybral, aby statki AI na planszy byly widoczne, w przeciwnym wypadku false.
*/
void przygotowanie_Gry(Plansza& p1, Plansza& ai, bool czy_Widoczna)
{
    p1.rysuj(false);
    ai.rysuj(true);

    p1.rozmiesc_Statki(false, true, p1.stworz_CzteroMasztowiec());
    p1.rozmiesc_Statki(false, true, p1.stworz_DwuMasztowiec());
    p1.rozmiesc_Statki(false, true, p1.stworz_JednoMasztowiec());
    //AI tworzy statki
    ai.rozmiesc_Statki(true, czy_Widoczna, ai.stworz_CzteroMasztowiec());
    Sleep(1000);
    ai.rozmiesc_Statki(true, czy_Widoczna, ai.stworz_DwuMasztowiec());
    Sleep(1000);
    ai.rozmiesc_Statki(true, czy_Widoczna, ai.stworz_JednoMasztowiec());
    Sleep(2000);
    system("cls");
}

/**
* Dalszy przebieg gry, naprzemienne strzelanie gracza z AI w nieskonczonej petli dopoki ktos nie zestrzeli statkow przeciwnika.
* 
* Pobiera dwie dane typu Plansza poprzez referencje.
* \param[in,out] p1 obiekt gracza.
* \param[in,out] ai obiekt AI.
* \return 0 jesli gra dobiegnie konca.
*/
int przebieg_Gry(Plansza& p1, Plansza& ai)
{
    for (;;)
    {

        ai.rysuj(true);
        Sleep(500);
        cout << "------------------------------" << endl;
        cout << "STRZELA AI" << endl;
        Sleep(1000);
        p1.strzelaj(false);
        p1.rysuj(false);
        Sleep(1200);
        if (p1.pobierz_zatopione_Statki() == 3)
        {
            system("cls");
            cout << "KONIEC GRY, WYGRALO AI" << endl;
            system("PAUSE");
            return 0;
        }
        else if (ai.pobierz_zatopione_Statki() == 3)
        {
            system("cls");
            cout << "KONIEC GRY, WYGRAL GRACZ" << endl;
            system("PAUSE");
            return 0;
        }
        cout << endl << "//////////////////////////////////" << endl;
        cout << "STRZELA GRACZ" << endl;
        ai.strzelaj(true);
        Sleep(1000);
        system("cls");

        if (p1.pobierz_zatopione_Statki() == 3)
        {
            cout << "KONIEC GRY, WYGRALO AI" << endl;
            system("PAUSE");
            return 0;
        }
        else if (ai.pobierz_zatopione_Statki() == 3)
        {
            cout << "KONIEC GRY, WYGRAL GRACZ" << endl;
            system("PAUSE");
            return 0;
        }
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    fstream instrukcja;
    bool czy_Widoczna;
    int wybor_Widocznosci;
    Plansza p1(10, 8); //WYMOGI: minimalny rozmiar planszy to 8x8, ZALECANY rozmiar planszy to 10x8!
    Plansza ai(10, 8); //Tworzy AI z planszą
   
    try
    {
       odczytaj_Instrukcje(instrukcja);
    }
    catch (runtime_error& e)
    {
        cout << "Blad wykonania programu: " << e.what() << endl;
        return 1;
    }

    ustaw_Widocznosc(wybor_Widocznosci, czy_Widoczna);

    przygotowanie_Gry(p1, ai, czy_Widoczna);

    przebieg_Gry(p1, ai);

}

