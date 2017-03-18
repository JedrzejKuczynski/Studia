// AKwB zad. IV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <numeric>
#include <ctime>

using namespace std;

vector<int> read_from_file(string name) {

	vector<int> multiset;
	name.append(".txt");
	ifstream f(name);

	if (f.good()) {

		int length;

		while (f >> length)
			multiset.push_back(length);
	}
	else
		cout << "Nie udalo sie otworzyc pliku!" << endl << endl;

	return multiset;
}

void show_multiset(vector<int> multiset) {

	for (int i = 0; i < multiset.size(); i++)
		cout << multiset[i] << " ";
}

void show_matrix(vector<vector<int>> matrix) {

	cout << "   ";
	for (int i = 0; i < matrix.size(); i++)
		cout << setw(3) << i;

	cout << endl << endl;

	for (int i = 0; i < matrix.size(); i++) {
		cout << setw(3) << i;
		for (int j = 0; j < matrix[i].size(); j++)
			cout << setw(3) << matrix[i][j];
		cout << endl;
	}
}

bool check_if_correct(int size, int &cuts) {

	for (int i = 0; i < 100; i++) {

		int k = i + 2;
		int elements = (k*(k - 1)) / 2;

		if (elements == size) {
			cuts = i;
			return true;
		}
		else if (elements > size)
			return false;
	}
	return false;
}

int check_if_exists(vector<int> multiset, int i) {

	int position;

	for (int j = 0; j < multiset.size(); j++)
		if (multiset[j] == i) {
			position = j;
			return position;
		}

	position = -1;
	return position;
}

bool continuation(vector<int>& map, vector<int>& numbers, vector<int>& used) {

	vector<int> tmp_numbers = numbers;
	vector<int> tmp_used = used;

	for (int i = 2; i <= map.size(); i++) {

		int sum = accumulate(map.rbegin(), map.rbegin() + i, 0);

		if (sum < tmp_numbers.size() && tmp_numbers[sum] > 0) {
			tmp_numbers[sum]--;
			tmp_used.push_back(sum);
		}
		else
			return false;

	}

	used = tmp_used;
	numbers = tmp_numbers;
	return true;
}

void search_for_solution(vector<int>& map, int size_of_map, bool& solution, vector<int> numbers, vector<int> used) {

	vector<int> forbidden;
	int check = 0;

	if (map.size() == size_of_map) {

		for (int i = 0; i < map.size(); i++)
			cout << map[i] << " ";

		solution = true;
	}
	else for (int i = 1; i < numbers.size(); i++) {

		if (numbers[i] > 0) {

			check = check_if_exists(forbidden, i);

			if (check == -1) {

				map.push_back(i);

				if (continuation(map, numbers, used)) {
					search_for_solution(map, size_of_map, solution, numbers, used);

					if (solution)
						break;

					numbers[i]++;

					for (int j = 1; j < map.size(); j++) {

						int tmp = used[used.size() - 1];
						used.pop_back();
						numbers[tmp]++;
					}
				}
				else
					forbidden.push_back(i);

				map.pop_back();

			}
		}
	}
}

int main()
{

	vector<int> multiset = read_from_file("ins-PDP-14b-desc");
	vector<int> numbers;
	vector<int> used;
	vector<int> map;
	double time_;
	clock_t start, finish;
	srand (time(NULL));

	cout.precision(2);
	cout.setf(ios::fixed);

	int cuts, size_of_map;

	sort(multiset.begin(), multiset.end());
	show_multiset(multiset);

	cout << endl << endl;

	if (check_if_correct(multiset.size(), cuts)) {

		size_of_map = cuts + 1;
		int beginning = multiset[multiset.size() - 1] - multiset[multiset.size() - 2];
		//int beginning_desc = multiset[0] - multiset[1];

		map.push_back(beginning);

		auto max = max_element(multiset.begin(), multiset.end());

		numbers.resize(*max + 1);

		for (int i = 0; i < multiset.size(); i++) {
			if (numbers[multiset[i]] == 0)
				numbers[multiset[i]] = 1;
			else
				numbers[multiset[i]]++;
		}

		numbers[beginning]--;
		used.push_back(beginning);

		cout << endl << endl;

		bool solution = false;
		cout.precision(2);

		start = clock();
		search_for_solution(map, size_of_map, solution, numbers, used);
		finish = clock();

		time_ = (finish - start) / (double)CLOCKS_PER_SEC;

		cout << endl << endl;

		if (time_ >= 60) {

			time_ /= (double)60;

			cout << "Czas wykonania sie algorytmu: " << time_ << " minut." << endl << endl;
		}
		else
			cout << "Czas wykonania sie algorytmu: " << time_ << " sekund." << endl << endl;


		if (!solution)
			cout << "Nie znaleziono rozwiazania!" << endl << endl;

	}
	else
		cout << "Licznoœæ multizbioru niepoprawna!" << endl << endl;


	cout << "\a\a\a\a";
	cout << endl << endl;
	system("PAUSE");
    return 0;
}

