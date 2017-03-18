// AKwB. zad. III.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph_h.h"

int main()
{

	int input, window, credibility;

	cout << "Podaj dlugosc podciagow (od 4 do 7): ";

	while(cin >> input){
		if(input < 4 || input > 7){
			cout << endl <<  "Podales zla wartosc!!!" << endl << endl;
			cout << "Podaj dlugosc podciagow (od 4 do 7): ";
		}else
			break;
	}

	window = input;

	cout << "Podaj granice wiarygodnosci (ponizej tej wartosci nukleotydy nie beda brane pod uwage; max 40): ";

	while(cin >> input){
		if(input > 40){
			cout << endl <<  "Podales zla wartosc!!!" << endl << endl;
			cout << "Podaj granice wiarygodnosci: ";
		}else
			break;
	}

	credibility = input;

	Graph g1 = Graph("dospr3", window, credibility);
	//g1.show_vertices();
	//g1.show_matrix();
	g1.max_clique_heur(3);
	cout << endl;
	g1.show_clique();
	cout << endl << endl;
	g1.clique_series();
	cout << endl << endl;
	g1.show_clique_series();

	system("PAUSE");
	return 0;
}

