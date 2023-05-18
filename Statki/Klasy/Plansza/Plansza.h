#pragma once
#include "..\Statek\Statek.h"
#include "..\Statek\CzteroMasztowiec.h"
#include "..\Statek\DwuMasztowiec.h"
#include "..\Statek\JednoMasztowiec.h"


class Plansza
{
protected:
	int szerokosc;
	int wysokosc;
	int zatopione_Statki;
	int licznik_DwuMasztowca;
	int licznik_CzteroMasztowca;
	int aktualne_x;
	int aktualne_y;
	int losuj_Orientacje_Dwumasztowca;
	int losuj_Orientacje_Czteromasztowca;
	//tablice
	char** polePlanszy;

	/**
	* Uzupelnia tablice wartosciami true wokol statku i w jego miejscu
	*/
	bool** czyZapelnione;

	/**
	* Przechowuje wartosc typu int 1 2 lub 4 na dlugosci statku w zaleznosci od jego rodzaju
	*/
	int** jaki_Statek_i_Pozycja; 
	//
	bool czyPion; //czy jest pionowo
	bool strzelaj_Wkolo;

public:
	Plansza(int szerokosc, int wysokosc);
	~Plansza();

	/**
	* Funkcja ta zwraca szerokosc planszy.
	*
	* \return szerokosc.
	*/
	int pobierz_Szerokosc();

	/**
	* Funkcja ta zwraca wysokosc planszy.
	*
	* \return wysokosc.
	*/
	int pobierz_Wysokosc();

	/**
	* Funkcja rysuje plansze ze wszystkimi obiektami dla gracza lub AI.
	*
	* Pobiera wartosc typu bool
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI, ma wartosc true jesli ruch wykonuje AI w przypadku ruchu gracza ma wartosc false.
	*/
	void rysuj(bool czy_AI);

	/**
	* Funkcja pobiera wszystkie niezbedne dane z obietku statku. 
	* Nastepnie uzupelnia wszystkie tablice klasy Plansza (poslugujac sie pobranymi danymi statku) w celu pozniejszego wyswietlenia statku na planszy,
	* mozliwosci jego rozmieszczenia wynikajacej ze stycznosci z innym statkiem i rozrozniania statkow
	*
	* Pobiera dwie wartosci typu bool oraz wskaznik typu Statek
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI, ma wartosc true jesli ruch wykonuje AI w przypadku ruchu gracza ma wartosc false.
	* \param[in] widocznosc_Planszy widocznosc statkow AI na planszy, ma wartosc true jesli gracz wybral, aby statki AI na planszy byly widoczne, w przeciwnym wypadku false.
	* \param[in,out] st obiekt statku.
	*/
	void rozmiesc_Statki(bool czy_AI,bool widocznosc_Planszy, Statek* st);

	/**
	* Funkcja sprawdza czy dany statek graniczy z innym.
	* 
	* Pobiera wskaznik typu Statek
	* \param[in,out] st obiekt statku.
	* \return true jesli statek graniczy z innym statkiem, w przeciwnym wypadku false.
	*/ 
	bool czy_Graniczy(Statek* st); //czy dany statek graniczy z innym

	/**
	* Funkcja ta tworzy obiekt czteromasztowca.
	*
	* \return zwraca wskaznik typu Statek na obiekt czteromasztowca.
	*/
	Statek* stworz_CzteroMasztowiec();

	/**
	* Funkcja ta tworzy obiekt dwumasztowca.
	*
	* \return zwraca wskaznik typu Statek na obiekt dwumasztowca.
	*/
	Statek* stworz_DwuMasztowiec();

	/**
	* Funkcja ta tworzy obiekt jednomasztowca.
	*
	* \return zwraca wskaznik typu Statek na obiekt jednomasztowca.
	*/
	Statek* stworz_JednoMasztowiec();

	/**
	* Tablica wskaznikow typu Statek o 3 miejscach stosowana do utworzenia obiektow roznych statkow. 
	*/
	Statek* obiekt_Statku[3];

	/**
	* Funkcja odpowiadajaca za system strzelania.
	* 
	* Jezeli ruch wykonuje AI oraz opcja strzelaj_Wkolo ma wartosc false, wspolrzedne strzalu sa wybierane losowo i wywolywana jest funkcja czy_Trafiono.
	* Jezeli ruch wykonuje AI oraz opcja strzelaj_Wkolo ma wartosc true, wspolrzedne strzalu sa wybierane losowo i wywolywana jest funkcja strzelaj_Ponownie.
	* Jezeli ruch wykonuje gracz to wspolrzedne strzalu sa wybierane przez niego i wywolywana jest funkcja czy_Trafiono.
	*
	* Pobiera wartosc typu bool.
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI, ma wartosc true jesli ruch wykonuje AI w przypadku ruchu gracza ma wartosc false.
	*/
	void strzelaj(bool czy_AI);

	/**
	* Funkcja odpowiadajaca za system ponownego strzelania dla AI (w przypadku trafienia w statek).
	* 
	* W przypadku trafienia w dwu lub czteromasztowca losowana jest orientacja ponownego strzalu (pion lub poziom).
	* Po wylosowaniu orientacji wspolrzedne ponownego strzalu sa losowane o jedno miejsce obok miejsca poprzedniego strzalu.
	* Informacja o nowym miejscu strzalu jest przesylana do funkcji czy_Trafiono.
	*
	* Pobiera wartosc typu bool oraz dwie wartosci typu int.
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI, ma wartosc true jesli ruch wykonuje AI w przypadku ruchu gracza ma wartosc false.
	* \param[in] x_Wylosowane wylosowona wspolrzedna x.
	* \param[in] y_Wylosowane wylosowona wspolrzedna y.
	*/
	void strzelaj_Ponownie(bool czy_AI, int x_Wylosowane, int y_Wylosowane);

	/**
	* Funkcja odpowiadajaca za sprawdzenie w co trafil strzal (puste pole, statek przeciwnika, miejsce w ktore juz strzelano).
	* 
	* W przypadku trafienia w statek przeciwnika miejsce strzalu zamieniane jest na 'X' i ustawiana jest wartosc zmiennej typu bool strzelaj_Wkolo na true. Zmienna
	* strzelaj_Wkolo odpowiada za strzelanie wokol poprzedniego strzalu.
	* W przypadku trafienia w puste pole miejsce strzalu zamieniane jest na '*'.
	* W przypadku trafienia w to samo miejsce wywoluje sie funkcja strzelaj.
	* 
	* W przypadku zatopienia statku zwiekszana jest zmienna typu int zatopione_Statki o jeden.
	* W przypadku zatopienia jednomasztowca ogwiazdkowujemy miejsce wokol niego i ustawiamy wartosc strzelaj_Wkolo na false.
	* W przypadku trafienia w dwumaszstowiec zwiekszamy zmienna licznik_DwuMasztowca o jeden (zliczajaca zestrzelone fragmenty statku). Jesli
	* licznik_DwuMasztowca == 2 to ustawiamy wartosc strzelaj_Wkolo na false.
	* W przypadku trafienia czteromasztowca zwiekszamy zmienna licznik_CzteroMasztowca o jeden. Jesli licznik_CzteroMasztowca >= 2
	* to ustawiamy wartosc strzelaj_Wkolo na false.
	*
	* Pobiera wartosc typu bool oraz dwie wartosci typu int.
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI, ma wartosc true jesli ruch wykonuje AI w przypadku ruchu gracza ma wartosc false.
	* \param[in] x_Wylosowane wylosowona wspolrzedna x.
	* \param[in] y_Wylosowane wylosowona wspolrzedna y.
	* \return 0 jesli zatopiono wszystkie statki przeciwnika (zmienna zatopione_Statki == 3)  lub AI zatopi pojedynczy statek.
	*/
	int czy_Trafiono(bool czy_AI, int x_Wylosowane, int y_Wylosowane);

	/**
	* Funkcja ta zwraca ilosc zatopionych statkow.
	*
	* \return zatopione_Statki.
	*/
	int pobierz_zatopione_Statki();

};