#pragma once
#include "Statek.h"
class DwuMasztowiec : public Statek
{
public:
	DwuMasztowiec();
	virtual bool ustaw_Wspolrzedne(int x, int y, int szerokosc, int wysokosc) override;
	virtual int pobierz_Wspolrzedna_X() override;
	virtual int pobierz_Wspolrzedna_Y() override;

	virtual int pobierz_Dlugosc() override;

	virtual bool czy_Mozna_Ustawic(int x, int y, int szerokosc, int wysokosc) override;
	virtual void ustaw_Statek(bool czy_AI, int szerokosc, int wysokosc) override;

	virtual void ustaw_CzyPion(bool czy_AI) override;
	virtual bool pobierz_CzyPion() override;
	virtual ~DwuMasztowiec();
};

