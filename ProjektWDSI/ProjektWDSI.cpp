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
	return 0;
}

