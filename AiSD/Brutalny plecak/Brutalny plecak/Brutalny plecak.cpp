// Brutalny plecak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

using namespace std;

int MAX;

void wypisz_el(int **tab_el, int elementy) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < elementy; j++)
			cout << setw(3) << tab_el[i][j];
		cout << endl;
	}

}

void brute_force(int poczatek, int wartosc, int waga, int x, int pojemnosc, int elementy, int** tab_el) {

	if (waga <= pojemnosc && wartosc > MAX)
		MAX = wartosc;

	for (int i = 0; i < elementy; i++)
		if (i > x && i != poczatek)
			brute_force(poczatek, wartosc + tab_el[1][i], waga + tab_el[2][i], i, pojemnosc, elementy, tab_el);
}

void przeglad(int elementy, int** tab_el, int pojemnosc) {

	for (int i = 0; i < elementy; i++)
		brute_force(i, tab_el[1][i], tab_el[2][i], 0, pojemnosc, elementy, tab_el);
	cout << endl << endl << MAX << endl;
}

int main()
{

	int pojemnosc, elementy, wartosc, waga;

	cout << "Podaj pojemnosc plecaka: ";
	cin >> pojemnosc;
	cout << "\nPodaj liczbe elementow: ";
	cin >> elementy;
	cout << endl;

	int **tab_el = new int *[3];

	for (int i = 0; i < 3; i++)
		tab_el[i] = new int[elementy];

	for (int i = 0;;) {
		int tmp = 1;
		for (int j = 0; j < elementy; j++) {
			tab_el[i][j] = tmp++;
		}
		break;
	}

	for (int j = 0; j < elementy; j++) {
		int tmp = 2;
		int i = 1;
		cout << "\nPodaj wartosc elementu " << j << ": ";
		cin >> wartosc;
		cout << "\nPodaj wage elementu " << j << ": ";
		cin >> waga;
		tab_el[i][j] = wartosc;
		tab_el[tmp][j] = waga;
	}
	cout << endl << endl;

	wypisz_el(tab_el, elementy);
	cout << endl << endl;

	przeglad(elementy, tab_el, pojemnosc);

	cout << endl << endl;

	system("PAUSE");
    return 0;
}

