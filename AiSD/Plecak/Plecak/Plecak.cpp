// Plecak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;


void wypisz_el(int **tab_el, int elementy) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < elementy; j++)
			cout << setw(3) << tab_el[i][j];
		cout << endl;
	}

}

void wypisz_w(int **tab_w, int elementy, int pojemnosc) {

	cout << "   ";

	for (int i = 1; i <= pojemnosc; i++)
		cout << setw(3) << i;

	cout << endl << endl;

	for (int i = 0; i <= elementy; i++) {
		for (int j = 0; j <= pojemnosc; j++)
			cout << setw(3) << tab_w[i][j];
		cout << endl;
	}

}

void wypisz_wynik(int elementy, int pojemnosc, int **tab_w, int **tab_wp, int **tab_el) {

	cout << "Maksymalna pojemnosc plecaka: " << pojemnosc << endl;
	cout << "Wartosc plecaka: " << tab_w[elementy][pojemnosc] << endl;


		while (pojemnosc > 0) {
			if (tab_wp[elementy][pojemnosc] == 0)
				elementy--;
			else {
				cout << "Element: " << tab_el[0][elementy - 1] << " Wartosc elementu: " << tab_el[1][elementy - 1] << " Waga elementu: " << tab_el[2][elementy - 1] << endl;
				pojemnosc = pojemnosc - tab_el[2][--elementy];
			}
			if (pojemnosc > 0 && elementy <= 0)
				break;
		}
}

void Plecak(int elementy, int pojemnosc, int **tab_w, int **tab_el, int **tab_wp) {

	int it = 0;

	for (int i = 1; i < elementy + 1; i++) {
		for (int j = 1; j < pojemnosc + 1; j++) {
			if (j < tab_el[2][it]) {
				tab_w[i][j] = tab_w[i - 1][j];
				tab_wp[i][j] = 0;
			}
			else {
				tab_w[i][j] = max(tab_w[i - 1][j], tab_w[i - 1][j - tab_el[2][it]] + tab_el[1][it]);
				if (tab_w[i - 1][j] > tab_w[i - 1][j - tab_el[2][it]] + tab_el[1][it])
					tab_wp[i][j] = 0;
				else
					tab_wp[i][j] = 1;
			}
		}
		it++;
	}
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

	int **tab_w = new int *[elementy + 1];

	for (int i = 0; i <= elementy; i++)
		tab_w[i] = new int[pojemnosc + 1];

	for (int i = 0; i <= elementy; i++)
		for (int j = 0; j <= pojemnosc; j++)
			tab_w[i][j] = 0;

	int **tab_wp = new int *[elementy + 1];

	for (int i = 0; i <= elementy; i++)
		tab_wp[i] = new int[pojemnosc + 1];

	for (int i = 0; i <= elementy; i++)
		for (int j = 0; j <= pojemnosc; j++)
			tab_wp[i][j] = 0;

	wypisz_w(tab_wp, elementy, pojemnosc);
	cout << endl << endl;
	Plecak(elementy, pojemnosc, tab_w, tab_el, tab_wp);
	wypisz_w(tab_w, elementy, pojemnosc);
	cout << endl << endl;
	wypisz_w(tab_wp, elementy, pojemnosc);
	cout << endl << endl;
	wypisz_wynik(elementy, pojemnosc, tab_w, tab_wp, tab_el);

	cout << endl << endl;
	system("PAUSE");
    return 0;
}

