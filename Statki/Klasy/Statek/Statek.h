#pragma once

class Statek
{
protected:
	int x, y;
	int dlugosc;

	/**
	* Zmienna bool sprawdzajaca czy statek jest ustawiony pionowo.
	*/ 
	bool czyPion;
public:
	Statek(int dlugosc, int x, int y);

	/**
	* Funkcja ta ustawia wspolrzedne odwolujac sie do funkcji czy_Mozna_Ustawic.
	* 
	* Pobiera cztery wartosci typu int i zwraca wartosc typu bool.
	* \param[in] x wspolrzedna na osi x.
	* \param[in] y wspolrzedna na osi y.
	* \param[in] szerokosc szerokosc planszy
	* \param[in] wysokosc wysokosc planszy
	* \return true jesli mozna ustawic wspolrzedne statku, false jesli nie mozna.
	*/
	virtual bool ustaw_Wspolrzedne(int x, int y, int szerokosc, int wysokosc) = 0;

	/**
	* Funkcja ta zwraca wspolrzedna x.
	*
	* \return x.
	*/
	virtual int pobierz_Wspolrzedna_X() = 0;

	/**
	* Funkcja ta zwraca wspolrzedna y.
	*
	* \return y.
	*/
	virtual int pobierz_Wspolrzedna_Y() = 0;

	/**
	* Funkcja ta zwraca dlugosc statku.
	*
	* \return dlugosc.
	*/
	virtual int pobierz_Dlugosc() = 0;

	/**
	* Funkcja ta sprawdza czy wspolrzedne statku mieszcza sie w granicach planszy.
	*
	* Pobiera cztery wartosci typu int i zwraca wartosc typu bool.
	* \param[in] x wspolrzedna na osi x.
	* \param[in] y wspolrzedna na osi y.
	* \param[in] szerokosc szerokosc planszy
	* \param[in] wysokosc wysokosc planszy
	* \return true jesli wspolrzedne statku mieszcza sie w granicach planszy, false jesli sie nie mieszcza.
	*/
	virtual bool czy_Mozna_Ustawic(int x, int y, int szerokosc, int wysokosc) = 0;

	/**
	* Funkcja pobiera wspolrzedne statku z klawiatury jesli zmienna bool czy_AI ma wartosc false,
	* a w przypadku wartosci true wspolrzedne sa pobierane losowo. Funkcja ta wywoluje funkcje
	* ustaw_Wspolrzedne w celu ustawienia statku.
	*
	* Pobiera wartosc typu bool i dwie wartosci typu int
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI.
	* \param[in] szerokosc szerokosc planszy
	* \param[in] wysokosc wysokosc planszy
	*/
	virtual void ustaw_Statek(bool czy_AI, int szerokosc, int wysokosc) = 0;

	/**
	* Funkcja ta ustawia orientacje statku zapisujac ja w zmiennej czyPion typu bool. Zmienna czyPion przyjmuje wartosc true jesli statek jest ustawiony pionowo w przeciwnym wypadku false.
	* 
	* \param[in] czy_AI zmienna rozrozniajaca gracza od AI.
	*/
	virtual void ustaw_CzyPion(bool czy_AI) = 0;

	/**
	* Funkcja ta zwraca orientacje statku.
	*
	* \return czyPion.
	*/
	virtual bool pobierz_CzyPion() = 0;

	virtual ~Statek();
};

