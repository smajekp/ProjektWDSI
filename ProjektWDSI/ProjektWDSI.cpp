// ProjektWDSI.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#define ZAKONCZ 0.000001
#define DLUGOSC 21
#define WLK_POP 64
#define ITER 20
#define PRAWD_MUT 0.2
#define PODZ_KRZYZ WLK_POP/4
using namespace std;

class osobnik{
public:
	int chromosom[DLUGOSC];
	double ocena;
	double x;
	osobnik(){
		for (int i = 0; i < DLUGOSC; i++)
		{
			chromosom[i] = rand() % 2;
		}
		ocena = 0;
	}
};

unsigned int przyst(osobnik &a){
	int suma = 0;
	for (int i = 0; i < DLUGOSC; i++)
	{
		suma += a.chromosom[i] * pow(2, i);
	}
	a.x = -1.0 + (2.0*suma) / (2097152 - 1);
	a.ocena = -a.x + sin(5 * a.x) - cos(13 * a.x);

	return a.ocena;
}
bool porownanie(osobnik &a, osobnik &b)
{
	if (a.ocena < b.ocena)
		return true;
	else
		return false;
}

void Sortuj_szybko(vector<osobnik> &d, int lewy, int prawy)
{
	int i, j;
	osobnik piwot = osobnik();
	i = (lewy + prawy) / 2;
	piwot = d[i]; d[i] = d[prawy];
	for (j = i = lewy; i < prawy; i++)
	if (d[i].ocena < piwot.ocena)
	{
		swap(d[i], d[j]);
		j++;
	}
	d[prawy] = d[j]; d[j] = piwot;
	if (lewy < j - 1)  Sortuj_szybko(d, lewy, j - 1);
	if (j + 1 < prawy) Sortuj_szybko(d, j + 1, prawy);
}



int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	vector<osobnik> populacja;
	vector<osobnik> newPopulacja;

	for (int i = 0; i < WLK_POP; i++)
	{
		osobnik os = osobnik();
		populacja.push_back(os);
	}

	for (int k = 0; k < ITER; k++)
	{

		for (int i = 0; i < WLK_POP; i++)
		{
			populacja[i].ocena = 0;
			przyst(populacja[i]);
		}

		Sortuj_szybko(populacja, 0, WLK_POP - 1);

		cout << k + 1 << ". ";
		for (int j = 0; j < DLUGOSC; j++)
		{
			cout << populacja[0].chromosom[j];
		}
		cout << "    " << populacja[0].ocena;
		cout << "    " << populacja[0].x;
		cout << endl;

		//if (abs((0.968694 - populacja[0].x)) < ZAKONCZ)
		//	break;

		//SELEKCJA TURNIEJOWA

		int q = 5; //liczba osobnikow
		vector <osobnik> uczestnicy;
		vector <osobnik> koncowaPopulacja;
		for (int j = 0; j < WLK_POP; j++)
		{

			for (int i = 0; i < q; i++)
			{
				int i1 = rand() % WLK_POP;
				uczestnicy.push_back(populacja[i1]);
			}

			Sortuj_szybko(uczestnicy, 0, q - 1);
			newPopulacja.push_back(uczestnicy[0]);
			for (int i = 0; i < q; i++)
			{
				uczestnicy.pop_back();
			}
		}

		// KRZY¯OWANIE JEDNOPUNKTOWE

		for (int i = 0; i < WLK_POP / 2; i++)
		{
			int i1 = rand() % WLK_POP;
			int i2 = rand() % WLK_POP;
			int punkt_podz = rand() % DLUGOSC;
			osobnik one = newPopulacja[i1];
			osobnik two = newPopulacja[i2];
			osobnik newOne = osobnik();
			osobnik newTwo = osobnik();

			for (int j = 0; j < punkt_podz; j++)
			{
				newOne.chromosom[j] = one.chromosom[j];
				newTwo.chromosom[j] = two.chromosom[j];
			}
			for (int j = punkt_podz; j < DLUGOSC; j++)
			{
				newOne.chromosom[j] = two.chromosom[j];
				newTwo.chromosom[j] = one.chromosom[j];
			}

			// MUTACJA

			if ((rand() % 100) < PRAWD_MUT * 100)
			{
				int x = rand() % DLUGOSC;
				if (newOne.chromosom[x] == 0)
				{
					newOne.chromosom[x] = 1;
				}
				else
					newOne.chromosom[x] = 0;
			}
			if ((rand() % 100) < PRAWD_MUT * 100)
			{
				int x = rand() % DLUGOSC;
				if (newTwo.chromosom[x] == 0)
				{
					newTwo.chromosom[x] = 1;
				}
				else
					newTwo.chromosom[x] = 0;
			}

			koncowaPopulacja.push_back(newOne);
			koncowaPopulacja.push_back(newTwo);
		}

		for (int i = 0; i < WLK_POP; i++)
		{
			populacja.pop_back();
			newPopulacja.pop_back();
		}
		for (int i = 0; i < WLK_POP; i++)
		{
			populacja.push_back(koncowaPopulacja[i]);
		}
		for (int i = 0; i < WLK_POP; i++)
		{
			koncowaPopulacja.pop_back();
		}

	}


	
	system("PAUSE");
	return 0;
}

