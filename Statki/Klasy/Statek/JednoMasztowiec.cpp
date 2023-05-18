#include "JednoMasztowiec.h"
#include <iostream>

using namespace std;

JednoMasztowiec::JednoMasztowiec() : Statek(1, 0, 0) {}; //Konstruktor

bool JednoMasztowiec::ustaw_Wspolrzedne(int x, int y, int szerokosc, int wysokosc)
{
	if (czy_Mozna_Ustawic(x, y, szerokosc, wysokosc))
	{
		this->x = x;
		this->y = y;
		return true;
	}
	else
		return false;
}

bool JednoMasztowiec::czy_Mozna_Ustawic(int x, int y, int szerokosc, int wysokosc)
{
	if (x >= 0 && x < szerokosc && y >= 0 && y < wysokosc)
	{
		if (czyPion)
		{
			if (y >= 0 && y <= (wysokosc - dlugosc))
				return true;
			else
				return false;
		}
		if (czyPion == false)
		{
			if (x >= 0 && x <= (szerokosc - dlugosc))
				return true;
			else
				return false;
		}
	}
	return false;
}
int JednoMasztowiec::pobierz_Wspolrzedna_X()
{
	return x;
}
int JednoMasztowiec::pobierz_Wspolrzedna_Y()
{
	return y;
}
int JednoMasztowiec::pobierz_Dlugosc()
{
	return dlugosc;
}
void JednoMasztowiec::ustaw_CzyPion(bool czy_AI)
{
	int wybor_Pozycji;
	if (czy_AI)
		wybor_Pozycji = rand() % 2 + 1;
	else
	{
		do
		{
			cout << "Aby umiescic statek pionowo wpisz 1, jesli w poziomie 2" << endl;
			while (!(cin >> wybor_Pozycji)) {
				cin.clear(); //skasuj bledny stan strumienia
				cin.ignore(999, '\n'); //zignoruj pozostale znaki w strumieniu
				cout << "Nie wprowadzono liczby" << endl;
			}
		} while (wybor_Pozycji != 1 && wybor_Pozycji != 2);
	}
		if (wybor_Pozycji == 1)
			czyPion = true;
		else czyPion = false;
}
bool JednoMasztowiec::pobierz_CzyPion()
{
	return czyPion;
}
void JednoMasztowiec::ustaw_Statek(bool czy_AI, int szerokosc, int wysokosc)
{
	int x, y;
	bool czy_Prawidlowe = true;
	if (czy_AI)
		cout << "AI losuje wspolrzedne" << endl;
	else
		cout << "Podaj wspolrzedne x i y" << endl;
	do
	{
		if (czy_AI)
		{
			x = rand() % szerokosc;
			y = rand() % wysokosc;
			czy_Prawidlowe = ustaw_Wspolrzedne(x, y, szerokosc, wysokosc);
		}
		else
		{
			while (!(cin >> x)) {
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Nie wprowadzono liczby" << endl;
			}
			while (!(cin >> y)) {
				cin.clear();
				cin.ignore(999, '\n');
				cout << "Nie wprowadzono liczby" << endl;
			}
			if (czy_Prawidlowe = ustaw_Wspolrzedne(x, y, szerokosc, wysokosc))
				break;
			else cout << "Te wartosci nie pasuja!" << endl;
		}
	} while (czy_Prawidlowe == false);
}

JednoMasztowiec::~JednoMasztowiec() {  };