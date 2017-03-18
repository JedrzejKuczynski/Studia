// AKwB - zad. II Mk II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class Graph {

	int V;
	vector<vector<int>> matrix;
	vector<vector<int>> matrix_or;
	bool multi;
	string name_or;

public:

	Graph(string name) {

		name_or = name;

		name.append(".txt");

		ifstream f(name);

		if (f.good()) {

			int v1, v2, size, arcs;

			f >> size;

			V = size;
			matrix.resize(V);

			f >> arcs;
			if (arcs > 1)
				multi = true;
			else
				multi = false;



			for (int i = 0; i < V; i++)
				matrix[i].resize(V);

			while (f >> v1 >> v2) {
				if (matrix[v1][v2] == 0)
					matrix[v1][v2] = 1;
				else
					matrix[v1][v2] += 1;
			}

			f.close();

		}
		else
			cout << "Nie udalo sie otworzyc pliku! Sprobuj ponownie." << endl << endl;
	}

	void ecce_machina() {

		show(matrix);
		cout << endl;

		if (check_adjoint() && multi == false) {

			cout << "Graf jest grafem sprzezonym." << endl << endl;

			if (check_line())
				cout << "Graf jest grafem liniowym." << endl << endl;
			else
				cout << "Graf nie jest grafem liniowym." << endl << endl;

			transform();
			show(matrix_or);
			cout << endl;
			write_to_file();
		}
		else
			cout << "Graf nie jest grafem sprzezonym." << endl << endl;
	}

private:

	bool check_line() {

		for (int i = 0; i < V; i++) {
			for (int j = i + 1; j < V; j++) {
				for (int k = 0; k < V; k++) {

					if (matrix[i][k] == 1 && matrix[i][k] == matrix[j][k]) {
						for (int l = 0; l < V; l++) {
							if (matrix[l][i] == 1 && matrix[l][i] == matrix[l][j])
								return false;
						}
						break;
					}	
				}
			}
		}

		return true;
	}

	bool check_adjoint() {

		for (int i = 0; i < V; i++) {
			for (int j = i + 1; j < V; j++) {
				for (int k = 0; k < V; k++) {

					if (matrix[i][k] == 1 && matrix[i][k] == matrix[j][k]) {
						for (int l = 0; l < V; l++) {
							if (matrix[i][l] != matrix[j][l])
								return false;
						}
						break;
					}
				}
			}
		}

		return true;
	}

	void transform() {

		vector<tuple<int, int, int>> connections;
		vector<pair<int, int>> adjusting;
		int max = 0;
		int tmp = 0;
		int min = 0;

		for (int i = 0; i < V; i++)
			connections.push_back(make_tuple(i, i * 2, i * 2 + 1));

		for (int i = 0; i < connections.size(); i++)
			for (int j = 0; j < connections.size(); j++) {
				if (matrix[i][j] == 1) {
					if (get<2>(connections[i]) < get<1>(connections[j]))
						get<1>(connections[j]) = get<2>(connections[i]);
					else if (get<2>(connections[i]) > get<1>(connections[j]))
						get<2>(connections[i]) = get<1>(connections[j]);
				}
			}

		/*for (int i = 0; i < connections.size(); i++)
			cout << "(" << get<0>(connections[i]) << ";" << get<1>(connections[i]) << ";" << get<2>(connections[i]) << "), ";*/

		//cout << endl << endl;

		for (int i = 0; i < connections.size(); i++)
			adjusting.push_back(make_pair(get<1>(connections[i]), get<2>(connections[i])));


		for (int i = 0; i < adjusting.size(); i++) {
			if (adjusting[i].first > max)
				max = adjusting[i].first;
			if (adjusting[i].second > max)
				max = adjusting[i].second;
		}

		while (min <= max) {

			for (int j = 0; j < adjusting.size(); j++) {
				if (min == adjusting[j].first || min == adjusting[j].second) {
					for (j; j < adjusting.size(); j++) {
						if (min == adjusting[j].first)
							adjusting[j].first = tmp;
						if (min == adjusting[j].second)
							adjusting[j].second = tmp;
					}
					tmp++;
					min++;
					break;
				}
				else if (j == adjusting.size() - 1)
					min++;
			}
		}

		//cout << endl << endl;

		/*for (int i = 0; i < adjusting.size(); i++)
			cout << "(" << adjusting[i].first << ";" << adjusting[i].second << "), ";*/

		max = 0;

		for (int i = 0; i < adjusting.size(); i++) {
			if (adjusting[i].first > max)
				max = adjusting[i].first;
			if (adjusting[i].second > max)
				max = adjusting[i].second;
		}
		max++;

		matrix_or.resize(max);

		for (int i = 0; i < max; i++) {
			matrix_or[i].resize(max);
		}


		for (int i = 0; i < adjusting.size(); i++) {
			if (matrix_or[adjusting[i].first][adjusting[i].second] == 0)
				matrix_or[adjusting[i].first][adjusting[i].second] = 1;
			else
				matrix_or[adjusting[i].first][adjusting[i].second]++;

		}
	}

	void write_to_file() {

		int arcs = 0;
		int tmp = 0;
		name_or.append("_or.txt");

		for (int i = 0; i < matrix_or.size(); i++) {
			for (int j = 0; j < matrix_or.size(); j++) {
				if (matrix_or[i][j] > arcs)
					arcs = matrix_or[i][j];
			}
		}

		ofstream f(name_or);

		if(f.good()){
			
			f << matrix_or.size() << endl;
			f << arcs << endl;

			for (int i = 0; i < matrix_or.size(); i++) {
				for (int j = 0; j < matrix_or.size(); j++) {
					if (matrix_or[i][j] > 0) {
						tmp = matrix_or[i][j];

						for (int k = 0; k < tmp; k++) {
							f << i << " " << j << endl;
						}
					}
				}
			}
			cout << "Zapis do pliku udany! Zyczymy milego dnia!" << endl << endl;
			f.close();
		}
		else
			cout << "Nie udalo sie otworzyc pliku do zapisu!" << endl << endl;
	}

	void show(vector<vector<int>> matrix) {

		cout << "   ";
		for (int i = 0; i < matrix.size(); i++)
			cout << setw(3) << i;

		cout << endl << endl;

		for (int i = 0; i < matrix.size(); i++) {
			cout << setw(3) << i;
			for (int j = 0; j < matrix.size(); j++)
				cout << setw(3) << matrix[i][j];
			cout << endl;
		}
	}
};

int main() {

	Graph g1 = Graph("grafspr4");
	
	cout << "Graf numer 1: " << endl << endl;
	g1.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	/*Graph g2 = Graph("graf2");

	cout << "Graf numer 2: " << endl << endl;
	g2.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g3 = Graph("graf3");

	cout << "Graf numer 3: " << endl << endl;
	g3.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g4 = Graph("graf4");

	cout << "Graf numer 4: " << endl << endl;
	g4.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g5 = Graph("graf5");

	cout << "Graf numer 5: " << endl << endl;
	g5.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g6 = Graph("graf6");

	cout << "Graf numer 6: " << endl << endl;
	g6.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g7 = Graph("graf7");

	cout << "Graf numer 7: " << endl << endl;
	g7.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g8 = Graph("graf8");

	cout << "Graf numer 8: " << endl << endl;
	g8.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g9 = Graph("graf9");

	cout << "Graf numer 9: " << endl << endl;
	g9.ecce_machina();
	cout << endl;


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	Graph g10 = Graph("graf10");

	cout << "Graf numer 10: " << endl << endl;
	g10.ecce_machina();
	cout << endl;*/


	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;
	system("PAUSE");
	return 0;
}