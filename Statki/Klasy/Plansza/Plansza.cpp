#include "Plansza.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Plansza::Plansza(int x, int y) :aktualne_x(0), aktualne_y(0), czyPion(false), licznik_DwuMasztowca(0),
licznik_CzteroMasztowca(0), zatopione_Statki(0), obiekt_Statku(), strzelaj_Wkolo(false), losuj_Orientacje_Dwumasztowca(0), losuj_Orientacje_Czteromasztowca(0)
{
	szerokosc = x;
	wysokosc = y;
	if (x < 8 || y < 8)
	{
		if (x < 8)
			szerokosc = 8;
		if (y < 8)
			wysokosc = 8;
	}
	/*Uzupelnienie tablicy charow*/
	polePlanszy = new char* [wysokosc];
	for (int i = 0; i < wysokosc; i++)
	{
		polePlanszy[i] = new char[szerokosc];
	}
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			polePlanszy[i][j] = '.';
		}
	}
	/*Uzupelnienie tablicy boolean*/
	czyZapelnione = new bool* [wysokosc];
	for (int i = 0; i < wysokosc; i++)
	{
		czyZapelnione[i] = new bool[szerokosc];
	}
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			czyZapelnione[i][j] = false;
		}
	}
	/*Uzupelnienie tablicy intow*/
	jaki_Statek_i_Pozycja = new int* [wysokosc];
	for (int i = 0; i < wysokosc; i++)
	{
		jaki_Statek_i_Pozycja[i] = new int[szerokosc];
	}
	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			jaki_Statek_i_Pozycja[i][j] = 0;
		}
	}
}

int Plansza::pobierz_Szerokosc()
{
	return szerokosc;
}
int Plansza::pobierz_Wysokosc()
{
	return wysokosc;
}
void Plansza::rysuj(bool czy_AI)
{
	if (czy_AI)
		cout << endl << "**PLANSZA AI**" << endl << endl;
	else
		cout << endl << "**PLANSZA GRACZA**" << endl << endl;

	char litera = 65;
	int liczba = 0;

	for (int j = 0; j < szerokosc; j++)	//Wypisanie cyfr nad plansza
	{
		cout << " " << liczba;
		liczba++;
	}	cout << endl;
	liczba = 0;
	for (int i = 0; i < wysokosc; i++)	//Wypisywanie planszy
	{
		for (int j = 0; j < szerokosc; j++)
		{
			cout << " " << polePlanszy[i][j];
		}
		cout << " " << liczba; //wypisanie z boku planszy
		liczba++;
		cout << endl;
	}
}
Statek* Plansza::stworz_CzteroMasztowiec()
{
	cout << endl << "**Stworz czteromasztowiec**" << endl;
	return obiekt_Statku[0] = new CzteroMasztowiec;
}
Statek* Plansza::stworz_DwuMasztowiec()
{
	cout << endl << "**Stworz dwumasztowiec**" << endl;
	return obiekt_Statku[1] = new DwuMasztowiec;
}
Statek* Plansza::stworz_JednoMasztowiec()
{
	cout << endl << "**Stworz jednomasztowiec**" << endl;
	return obiekt_Statku[2] = new JednoMasztowiec;
}
bool Plansza::czy_Graniczy(Statek* st)
{
	int licznik_Wolnych_Pol = 0;
	int x = st->pobierz_Wspolrzedna_X();
	int y = st->pobierz_Wspolrzedna_Y();
	int dlugosc_St = st->pobierz_Dlugosc();
	if (st->pobierz_CzyPion())
	{
		for (int i = 0; i < dlugosc_St; i++)
		{
			if (czyZapelnione[y][x] == false)
				licznik_Wolnych_Pol++;
			y++;
		}
	}
	else
	{
		for (int i = 0; i < dlugosc_St; i++)
		{
			if (czyZapelnione[y][x] == false)
				licznik_Wolnych_Pol++;
			x++;
		}
	}
	if (licznik_Wolnych_Pol == dlugosc_St)
		return false;
	else return true;
}
void Plansza::rozmiesc_Statki(bool czy_AI, bool widocznosc_Planszy, Statek* st) 
{
	int x;
	int y;
	st->ustaw_CzyPion(czy_AI);
	do
	{
		st->ustaw_Statek(czy_AI, szerokosc, wysokosc);
		x = st->pobierz_Wspolrzedna_X();
		y = st->pobierz_Wspolrzedna_Y();
		if (czy_Graniczy(st))
		{
			cout << "Statek graniczy z innym statkiem!" << endl;
		}
	} while (czy_Graniczy(st));

	int x_Poczatkowe = st->pobierz_Wspolrzedna_X();
	int y_Poczatkowe = st->pobierz_Wspolrzedna_Y();
	int dlugosc_St = st->pobierz_Dlugosc();
	if (st->pobierz_CzyPion())
	{
		//warunki braku stycznosci z innym statkiem- poczatek cz 1
		if (y >= 1)
		{
			if (x <= (szerokosc - 2))
				czyZapelnione[y - 1][x + 1] = true;				
			
			if (x >= 1)			
				czyZapelnione[y - 1][x - 1] = true;				
			
			czyZapelnione[y - 1][x] = true;
		}
		//koniec
		for (int i = 0; i < dlugosc_St; i++)
		{
			if(czy_AI == false || widocznosc_Planszy)
				polePlanszy[y][x] = 'O'; //pobieranie na odwrot y z x bo cos jest namieszane :)

			if (dlugosc_St == 4)
				jaki_Statek_i_Pozycja[y][x] = 4;
			else if (dlugosc_St == 2)
				jaki_Statek_i_Pozycja[y][x] = 2;
			else
				jaki_Statek_i_Pozycja[y][x] = 1;

			czyZapelnione[y][x] = true;
			//warunki braku stycznosci z innym statkiem- cz 2
			if (x <= (szerokosc - 2))
				czyZapelnione[y][x + 1] = true;			

			if (x >= 1)				
				czyZapelnione[y][x - 1] = true;
			
			//koniec
			y++;
		}
		//warunki braku stycznosci z innym statkiem- cz 3(ostatnia)
		if (y_Poczatkowe < (wysokosc - dlugosc_St))
		{
			if (x <= (szerokosc - 2))
				czyZapelnione[y][x + 1] = true;
			
			if (x >= 1)
				czyZapelnione[y][x - 1] = true;
			
			czyZapelnione[y][x] = true;
		}
		//koniec
		system("cls");
		rysuj(czy_AI);
	}
	else
	{
		//warunki braku stycznosci z innym statkiem- poczatek cz 1
		if (x >= 1)
		{
			if (y_Poczatkowe >= 1)
				czyZapelnione[y - 1][x - 1] = true;			

			if (y_Poczatkowe <= (wysokosc - 2))
				czyZapelnione[y + 1][x - 1] = true;			

			czyZapelnione[y][x - 1] = true;
		}
		//koniec
		for (int i = 0; i < dlugosc_St; i++)
		{
			if (czy_AI == false || widocznosc_Planszy)
				polePlanszy[y][x] = 'O';

			if (dlugosc_St == 4)
				jaki_Statek_i_Pozycja[y][x] = 4;
			else if (dlugosc_St == 2)
				jaki_Statek_i_Pozycja[y][x] = 2;
			else
				jaki_Statek_i_Pozycja[y][x] = 1;

			czyZapelnione[y][x] = true;
			//warunki braku stycznosci z innym statkiem- cz 2
			if (y_Poczatkowe <= (wysokosc - 2))
				czyZapelnione[y + 1][x] = true;			

			if (y_Poczatkowe >= 1)
				czyZapelnione[y - 1][x] = true;			

			//koniec
			x++;
		}
		//warunki braku stycznosci z innym statkiem- cz 3(ostatnia)
		if (x_Poczatkowe < (szerokosc - dlugosc_St))
		{
			if (y_Poczatkowe >= 1)
				czyZapelnione[y - 1][x] = true;			

			if (y_Poczatkowe <= (wysokosc - 2))
				czyZapelnione[y + 1][x] = true;			

			czyZapelnione[y][x] = true;
		}
		//koniec
		system("cls");
		rysuj(czy_AI);
	}

}
//***************************************************************
//AI

void Plansza::strzelaj(bool czy_AI)
{
	int x_Strzalu;
	int y_Strzalu;
	if (czy_AI == false && strzelaj_Wkolo == false) //na odwrot zeby dzialalo :)
	{
		x_Strzalu = rand() % pobierz_Szerokosc();
		y_Strzalu = rand() % pobierz_Wysokosc();
		czy_Trafiono(czy_AI, x_Strzalu, y_Strzalu);
	}
	else if (czy_AI == false && strzelaj_Wkolo == true)
	{
		x_Strzalu = aktualne_x;
		y_Strzalu = aktualne_y;
		strzelaj_Ponownie(czy_AI, x_Strzalu, y_Strzalu);
	}
	else
	{
		do
		{
			cout << "Wprowadz wspolrzedne strzalu" << endl;
			{
				while (!(cin >> x_Strzalu)) {
					cin.clear();
					cin.ignore(999, '\n');
					cout << "Nie wprowadzono liczby" << endl;
				}
				while (!(cin >> y_Strzalu)) {
					cin.clear();
					cin.ignore(999, '\n');
					cout << "Nie wprowadzono liczby" << endl;
				}
				
			}
		} while (!(x_Strzalu >= 0 && x_Strzalu < szerokosc && y_Strzalu >= 0 && y_Strzalu < wysokosc));
		czy_Trafiono(czy_AI, x_Strzalu, y_Strzalu);
	}
		
}
void Plansza::strzelaj_Ponownie(bool czy_AI, int x_Wylosowane, int y_Wylosowane)
{
	int x_Wylosowane_Ponownie = 0;
	int y_Wylosowane_Ponownie = 0;
	bool wyszlo_poza_Zero = false;
	bool wyszlo_poza_Plansze = false;
	int licznik_Poziom = 0;
	int licznik_Pion = 0;

	int losuj = 0;
	//DLA DWUMASZTOWCA
	if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 2)
	{
		losuj_Orientacje_Dwumasztowca = rand() % 2 + 1;  //1- pionowo, 2-poziomo
		if (losuj_Orientacje_Dwumasztowca == 1)
		{
			x_Wylosowane_Ponownie = x_Wylosowane;
			do
			{
				//cout << "petla w pionie" << endl;
				if (wyszlo_poza_Zero == true)
					y_Wylosowane_Ponownie = (y_Wylosowane + 1);
				else if (wyszlo_poza_Plansze == true)
					y_Wylosowane_Ponownie = (y_Wylosowane - 1);
				else
				{
					losuj = rand() % 2 + 1;
					if (losuj == 1)
						y_Wylosowane_Ponownie = y_Wylosowane + 1;
					else if (losuj == 2)
						y_Wylosowane_Ponownie = y_Wylosowane - 1;
				}
					

				if (y_Wylosowane_Ponownie < 0)
				{
					wyszlo_poza_Zero = true;
					y_Wylosowane_Ponownie = 0;
				}
				else if (y_Wylosowane_Ponownie > (wysokosc - 1))
				{
					wyszlo_poza_Plansze = true;
					y_Wylosowane_Ponownie = (wysokosc - 1);
				}

			} while (y_Wylosowane_Ponownie == y_Wylosowane);
		}
		else if (losuj_Orientacje_Dwumasztowca == 2)
		{
			y_Wylosowane_Ponownie = y_Wylosowane;
			do
			{
				//cout << "petla w poziom" << endl;
				if (wyszlo_poza_Zero == true)
					x_Wylosowane_Ponownie = (x_Wylosowane + 1);
				else if (wyszlo_poza_Plansze == true)
					x_Wylosowane_Ponownie = (x_Wylosowane - 1);
				else
				{
					losuj = rand() % 2 + 1;
					if (losuj == 1)
						x_Wylosowane_Ponownie = x_Wylosowane + 1;
					else if (losuj == 2)
						x_Wylosowane_Ponownie = x_Wylosowane - 1;
				}
					

				if (x_Wylosowane_Ponownie < 0)
				{
					wyszlo_poza_Zero = true;
					x_Wylosowane_Ponownie = 0;
				}
				else if (x_Wylosowane_Ponownie > (szerokosc - 1))
				{
					wyszlo_poza_Plansze = true;
					x_Wylosowane_Ponownie = (szerokosc - 1);
				}

			} while (x_Wylosowane_Ponownie == x_Wylosowane);
		}
	}
	//DLA CZTEROMASZTOWCA
	else if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 4)
	{
		if(licznik_CzteroMasztowca < 2)
			losuj_Orientacje_Czteromasztowca = rand() % 2 + 1;
		if (losuj_Orientacje_Czteromasztowca == 1)
		{
			//licznik_Pion++;
			x_Wylosowane_Ponownie = x_Wylosowane;
			do
			{
				//cout << "petla w pionie" << endl;
				if (wyszlo_poza_Zero == true)
					y_Wylosowane_Ponownie = (y_Wylosowane + 1);
				else if (wyszlo_poza_Plansze == true)
					y_Wylosowane_Ponownie = (y_Wylosowane - 1);
				else
				{
					losuj = rand() % 2 + 1;
					if (losuj == 1)
						y_Wylosowane_Ponownie = y_Wylosowane + 1;
					else if (losuj == 2)
						y_Wylosowane_Ponownie = y_Wylosowane - 1;
				}
					

				if (y_Wylosowane_Ponownie < 0)
				{
					wyszlo_poza_Zero = true;
					y_Wylosowane_Ponownie = 0;
				}
				else if (y_Wylosowane_Ponownie > (wysokosc - 1))
				{
					wyszlo_poza_Plansze = true;
					y_Wylosowane_Ponownie = (wysokosc - 1);
				}

			} while (y_Wylosowane_Ponownie == y_Wylosowane);
		}
		else if (losuj_Orientacje_Czteromasztowca == 2)
		{
			//licznik_Poziom++;
			y_Wylosowane_Ponownie = y_Wylosowane;
			do
			{
				//cout << "petla w poziom" << endl;

				if (wyszlo_poza_Zero == true)
					x_Wylosowane_Ponownie = (x_Wylosowane + 1);
				else if (wyszlo_poza_Plansze == true)
					x_Wylosowane_Ponownie = (x_Wylosowane - 1);
				else
				{
					losuj = rand() % 2 + 1;
					if (losuj == 1)
						x_Wylosowane_Ponownie = x_Wylosowane + 1;
					else if(losuj == 2)
						x_Wylosowane_Ponownie = x_Wylosowane - 1;
				}

				if (x_Wylosowane_Ponownie < 0)
				{
					wyszlo_poza_Zero = true;
					x_Wylosowane_Ponownie = 0;
				}
				else if (x_Wylosowane_Ponownie > (szerokosc - 1))
				{
					wyszlo_poza_Plansze = true;
					x_Wylosowane_Ponownie = (szerokosc - 1);
				}

			} while (x_Wylosowane_Ponownie == x_Wylosowane);
		}
	}
	

	x_Wylosowane = x_Wylosowane_Ponownie;
	y_Wylosowane = y_Wylosowane_Ponownie;
	czy_Trafiono(czy_AI, x_Wylosowane_Ponownie, y_Wylosowane_Ponownie);

}
int Plansza::czy_Trafiono(bool czy_AI, int x_Wylosowane, int y_Wylosowane)
{
	if (czy_AI == false) //jesli strzela ai
	{
		if (polePlanszy[y_Wylosowane][x_Wylosowane] == 'O')
		{
			strzelaj_Wkolo = true;
			aktualne_x = x_Wylosowane;
			aktualne_y = y_Wylosowane;
			if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 1)
			{
				strzelaj_Wkolo = false;
				int x = x_Wylosowane; //pomocnicze zmienne wspolrzednych
				int y = y_Wylosowane; 
				for (int i = 0; i < 3; i++) //ogwiazdkowanie miejsca wokol jednomasztowca
				{
					if (y - 1 < 0)
					{
						y++;
						continue;
					}
					else if (y - 1 > wysokosc - 1)
					{
						continue;
					}
					for (int j = 0; j < 3; j++)
					{
						if (x - 1 < 0)
						{
							x = x + 1;
							continue;
						}
						else if(x - 1 > szerokosc - 1)
						{
							continue;
						}
						polePlanszy[y - 1][x - 1] = '*';
						x++;
					}
					x = x_Wylosowane;
					y++;
				}
				polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';
				cout << "Zatopiono jednomasztowiec\a" << endl; //Efekty dzwiekowe
				zatopione_Statki++;
				if (pobierz_zatopione_Statki() == 3)
					return 0;
				strzelaj(czy_AI);
				return 0;
			}
			else if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 2)
			{
				licznik_DwuMasztowca++;
				polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';

				if (licznik_DwuMasztowca == 2)
				{
					strzelaj_Wkolo = false;
					
					polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';
					cout << "Zatopiono dwumasztowiec\a" << endl; //Efekty dzwiekowe
					zatopione_Statki++;
					if (pobierz_zatopione_Statki() == 3)
						return 0;
					cout << "trafiono, strzelaj jeszcze raz" << endl;
					strzelaj(czy_AI);
					return 0;
				}
			}
			else if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 4)
			{
				licznik_CzteroMasztowca++;
			
				if (licznik_CzteroMasztowca == 2 && (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane - 1] == 4 || jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane + 1] == 4))
					losuj_Orientacje_Czteromasztowca = 2; //poziom

				else if (licznik_CzteroMasztowca == 2 && (jaki_Statek_i_Pozycja[y_Wylosowane - 1][x_Wylosowane] == 4 || jaki_Statek_i_Pozycja[y_Wylosowane + 1][x_Wylosowane] == 4))
					losuj_Orientacje_Czteromasztowca = 1; //pion

				polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';

				if (licznik_CzteroMasztowca >= 2)
					strzelaj_Wkolo = false;

				if (licznik_CzteroMasztowca == 4)
				{
					strzelaj_Wkolo = false;
					cout << "Zatopiono czteromasztowiec\a" << endl; //Efekty dzwiekowe
					zatopione_Statki++;
					if (pobierz_zatopione_Statki() == 3)
						return 0;
					cout << "trafiono, strzelaj jeszcze raz" << endl;
					strzelaj(czy_AI);
					return 0;
				}
			}

			cout << "trafiono, strzelaj jeszcze raz" << endl;
			strzelaj_Ponownie(czy_AI, x_Wylosowane, y_Wylosowane);
		}
		else if (polePlanszy[y_Wylosowane][x_Wylosowane] == '.')
		{
			polePlanszy[y_Wylosowane][x_Wylosowane] = '*';
			cout << "wolne miejsce" << endl;
		}
		else if (polePlanszy[y_Wylosowane][x_Wylosowane] == '*' || polePlanszy[y_Wylosowane][x_Wylosowane] == 'X')
		{
			//cout << "to samo miejsce" << endl;
			strzelaj(czy_AI);
		}
	}
	else //jesli strzela gracz
	{
		if (polePlanszy[y_Wylosowane][x_Wylosowane] == '*' || polePlanszy[y_Wylosowane][x_Wylosowane] == 'X')
		{
			cout << "to samo miejsce" << endl;
			strzelaj(czy_AI);
		}
		else if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 1)
		{
			int x = x_Wylosowane; //pomocnicze zmienne wspolrzednych
			int y = y_Wylosowane;
			for (int i = 0; i < 3; i++)
			{
				if (y - 1 < 0)
				{
					y++;
					continue;
				}
				else if (y - 1 > wysokosc - 1)
				{
					continue;
				}
				for (int j = 0; j < 3; j++)
				{
					if (x - 1 < 0)
					{
						x = x + 1;
						continue;
					}
					else if (x - 1 > szerokosc - 1)
					{
						continue;
					}
					polePlanszy[y - 1][x - 1] = '*';
					x++;
				}
				x = x_Wylosowane;
				y++;
			}
			polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';
			cout << "Zatopiono jednomasztowiec\a" << endl; //Efekty dzwiekowe
			zatopione_Statki++;
			if (pobierz_zatopione_Statki() == 3)
				return 0;
			cout << "trafiono, strzelaj jeszcze raz" << endl;

			rysuj(czy_AI);
			strzelaj(czy_AI);
		}
		else if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 2)
		{
			licznik_DwuMasztowca++;
			polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';

			if (licznik_DwuMasztowca == 2)
			{
				cout << "Zatopiono dwumasztowiec\a" << endl; //Efekty dzwiekowe
				zatopione_Statki++;

			}
			if (pobierz_zatopione_Statki() == 3)
				return 0;
			cout << "trafiono, strzelaj jeszcze raz" << endl;

			rysuj(czy_AI);
			strzelaj(czy_AI);
		}
		else if (jaki_Statek_i_Pozycja[y_Wylosowane][x_Wylosowane] == 4)
		{
			licznik_CzteroMasztowca++;
			polePlanszy[y_Wylosowane][x_Wylosowane] = 'X';

			if (licznik_CzteroMasztowca == 4)
			{
				cout << "Zatopiono czteromasztowiec\a" << endl; //Efekty dzwiekowe
				zatopione_Statki++;

			}
			if (pobierz_zatopione_Statki() == 3)
				return 0;

			cout << "trafiono, strzelaj jeszcze raz" << endl;
	
			rysuj(czy_AI);
			strzelaj(czy_AI);
		}
		else if (polePlanszy[y_Wylosowane][x_Wylosowane] == '.')
		{
			polePlanszy[y_Wylosowane][x_Wylosowane] = '*';
			cout << "wolne miejsce" << endl;
		}

	}
		return 0;
}
int Plansza::pobierz_zatopione_Statki()
{
	return zatopione_Statki;
}

//Destruktor
Plansza::~Plansza()
{
	/*usuwanie tablicy charow*/
	for (int i = 0; i < wysokosc; i++)
	{
		delete[] polePlanszy[i];
	}
	delete[] polePlanszy;
	/*usuwanie tablicy boolean*/
	for (int i = 0; i < wysokosc; i++)
	{
		delete[] czyZapelnione[i];
	}
	delete[] czyZapelnione;
	/*usuwanie tablicy intow*/
	for (int i = 0; i < wysokosc; i++)
	{
		delete[] jaki_Statek_i_Pozycja[i];
	}
	delete[] jaki_Statek_i_Pozycja;
	//usuwanie obiektow statkow
	for (int i = 0; i < 2; ++i)
		delete[] obiekt_Statku[i];
}

