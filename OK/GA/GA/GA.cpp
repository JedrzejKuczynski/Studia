// GA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

class Job {

public:

	int job_id;
	tuple<int, int, int> op1; //czas, maszyna, czas gotowoœci
	pair<int, int> op2; // czas, maszyna

	Job(int i, vector<int> parameters) {
		
		job_id = i;

		op1 = make_tuple(parameters[0], parameters[2], parameters[4]);
		op2 = make_pair(parameters[1], parameters[3]);
	}

	~Job() {}
};

vector<Job> read_from_file(int i, vector<tuple<int, int, int, int>>& maint1) {
	
	string s_i = to_string(i);
	string filename = "ins_in_";
	filename.append(s_i);
	filename.append(".txt");
	ifstream f(filename);

	vector<Job> jobs;

	if (f.good()) {

		int n_jobs;
		string line;
		string value;
		int counter = 0;

		f >> n_jobs;
		getline(f, line);

		while(getline(f, line)) {

			if (counter < n_jobs) {

				vector<int> parameters;
				istringstream linestream(line);

				while (getline(linestream, value, ';'))
					parameters.push_back(stoi(value));

				Job new_job = Job(counter, parameters);
				jobs.push_back(new_job);

				counter++;
			}
			else {

				vector<int> parameters;
				istringstream linestream(line);

				while (getline(linestream, value, ';'))
					parameters.push_back(stoi(value));

				auto new_maint = make_tuple(parameters[0], parameters[1], parameters[2], parameters[3]);
				maint1.push_back(new_maint);
			}

		}
		f.close();
	}
	else
		cout << "Nie udalo sie otworzyc pliku!" << endl << endl;

	return jobs;
}

vector<vector<Job>> initialize_population(vector<Job> jobs, int size) {

	vector<vector<Job>> population;
	vector<int> used;
	vector<Job> phenotype;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < jobs.size(); j++) {

			int id = rand() % jobs.size();
			if (used.size() < jobs.size()) {
				while (find(begin(used), end(used), id) != end(used))
					id = rand() % jobs.size();
		}
			used.push_back(id);
			phenotype.push_back(jobs[id]);
		}
		population.push_back(phenotype);
		phenotype.clear();
		used.clear();
	}

	return population;
}

pair<int, int> check_maintenance(Job job, vector<tuple<int, int, int, int>> maint1, int new_start, int operation, int readyt2){
	
	// maint1 <nr_przerwy, nr_maszyny, czas trwania, czas startu>
	pair<int, int> new_parameters; // czas, czas gotowoœci

	sort(maint1.begin(), maint1.end(), [](auto const &t1, auto const &t2) {
		return get<3>(t1) < get<3>(t2);
	});

	if (operation == 1) {

		if (new_start == -1) {
			new_parameters = make_pair(get<0>(job.op1), get<2>(job.op1)); // czas, czas gotowoœci
			for (int i = 0; i < maint1.size(); i++) {
				if ((new_parameters.second >= get<3>(maint1[i]) && (new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i]))) || ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i])) && ((new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i])))) || ((new_parameters.second <= (get<3>(maint1[i]) + get<2>(maint1[i]))) && ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i]) + get<2>(maint1[i])))) || (new_parameters.second < get<3>(maint1[i]) && ((new_parameters.first + new_parameters.second) > (get<3>(maint1[i]) + get<2>(maint1[i]))))) {
					new_parameters = make_pair(get<0>(job.op1), (get<3>(maint1[i]) + get<2>(maint1[i])));
				}
			}
		}
		else {
			int new_readyt;
			int new_end;
			if (new_start < get<2>(job.op1)) {
				new_readyt = get<2>(job.op1);
				new_end = new_readyt + get<0>(job.op1);
			}
			else {
				new_readyt = new_start;
				new_end = new_readyt + get<0>(job.op1);
			}
			new_parameters = make_pair(get<0>(job.op1), new_readyt); // czas, czas gotowoœci

			for (int i = 0; i < maint1.size(); i++) {
				if ((new_parameters.second >= get<3>(maint1[i]) && (new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i]))) || ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i])) && ((new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i])))) || ((new_parameters.second <= (get<3>(maint1[i]) + get<2>(maint1[i]))) && ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i]) + get<2>(maint1[i])))) || (new_parameters.second < get<3>(maint1[i]) && ((new_parameters.first + new_parameters.second) > (get<3>(maint1[i]) + get<2>(maint1[i]))))) {
					new_parameters = make_pair(get<0>(job.op1), (get<3>(maint1[i]) + get<2>(maint1[i])));
				}
			}
		}
	}
	else {

		if (new_start == -1) {
			new_parameters = make_pair(get<0>(job.op2), readyt2); // czas, czas gotowoœci
			for (int i = 0; i < maint1.size(); i++) {
				if ((new_parameters.second >= get<3>(maint1[i]) && (new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i]))) || ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i])) && ((new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i])))) || ((new_parameters.second <= (get<3>(maint1[i]) + get<2>(maint1[i]))) && ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i]) + get<2>(maint1[i])))) || (new_parameters.second < get<3>(maint1[i]) && ((new_parameters.first + new_parameters.second) > (get<3>(maint1[i]) + get<2>(maint1[i]))))) {
					new_parameters = make_pair(get<0>(job.op2), (get<3>(maint1[i]) + get<2>(maint1[i])));
				}
			}
		}
		else {
			int new_readyt = new_start;
			int new_end = new_readyt + get<0>(job.op2);
			new_parameters = make_pair(get<0>(job.op2), new_readyt); // czas, czas gotowoœci

			for (int i = 0; i < maint1.size(); i++) {
				if ((new_parameters.second >= get<3>(maint1[i]) && (new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i]))) || ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i])) && ((new_parameters.first + new_parameters.second) <= (get<3>(maint1[i]) + get<2>(maint1[i])))) || ((new_parameters.second <= (get<3>(maint1[i]) + get<2>(maint1[i]))) && ((new_parameters.first + new_parameters.second) >= (get<3>(maint1[i]) + get<2>(maint1[i])))) || (new_parameters.second < get<3>(maint1[i]) && ((new_parameters.first + new_parameters.second) > (get<3>(maint1[i]) + get<2>(maint1[i]))))) {
					new_parameters = make_pair(get<0>(job.op2), (get<3>(maint1[i]) + get<2>(maint1[i])));
				}
			}
		}
	}
	return new_parameters;
}

int check_others(vector<tuple<int, int, int, int>> m, Job job, int operation, int readyt2) {

	// m <start, koniec, job_id, op_id>
	int new_start = -1;

	if (m.empty())
		return new_start;

	if (operation == 1) {
		if (get<2>(job.op1) < get<1>(m[m.size() - 1])) {
			new_start = get<1>(m[m.size() - 1]);
			return new_start;
		}
	}
	else {
		if (readyt2 < get<1>(m[m.size() - 1])) {
			new_start = get<1>(m[m.size() - 1]);
			return new_start;
		}
	}

	return new_start;
}

vector<pair<int, int>> decode_and_evaluate(vector<vector<Job>> population, vector<tuple<int, int, int, int>> maint1, pair<vector<Job>, int>& the_best) {

	// maint1 <nr_przerwy, nr_maszyny, czas trwania, czas startu>
	vector<pair<int, int>> fitness; // id, fitness

	for (int i = 0; i < population.size(); i++) {

		vector<tuple<int, int, int, int>> m1; // <start, koniec, job_id, op_id>
		vector<tuple<int, int, int, int>> m2; // <start, koniec, job_id, op_id>
		int readyt2 = 0;

		for (int j = 0; j < population[i].size(); j++) {
			if ((get<1>(population[i][j].op1)) == 1) {
				int new_start = check_others(m1, population[i][j], 1, readyt2);
				pair<int, int> new_parameters = check_maintenance(population[i][j], maint1, new_start, 1, readyt2); // czas, czas gotowoœci
				auto new_tuple = make_tuple(new_parameters.second, (new_parameters.second + new_parameters.first), population[i][j].job_id, 1);
				m1.push_back(new_tuple);
				readyt2 = new_parameters.second + new_parameters.first;
				new_start = check_others(m2, population[i][j], 2, readyt2);
				if (new_start == -1) {
					new_tuple = make_tuple(readyt2, (readyt2 + get<0>(population[i][j].op2)), population[i][j].job_id, 2);
					m2.push_back(new_tuple);
				}
				else {
					new_tuple = make_tuple(new_start, (new_start + get<0>(population[i][j].op2)), population[i][j].job_id, 2);
					m2.push_back(new_tuple);
				}
					
			}
			else {
				int new_start = check_others(m2, population[i][j], 1, readyt2);
				if (new_start == -1) {
					auto new_tuple = make_tuple((get<2>(population[i][j].op1)), (get<2>(population[i][j].op1) + get<0>(population[i][j].op1)), population[i][j].job_id, 1);
					readyt2 = (get<2>(population[i][j].op1) + get<0>(population[i][j].op1));
					m2.push_back(new_tuple);
				}
				else {
					auto new_tuple = make_tuple(new_start, (new_start + get<0>(population[i][j].op1)), population[i][j].job_id, 1);
					readyt2 = (new_start + get<0>(population[i][j].op1));
					m2.push_back(new_tuple);
				}
				new_start = check_others(m1, population[i][j], 2, readyt2);
				pair<int, int> new_parameters = check_maintenance(population[i][j], maint1, new_start, 2, readyt2);
				auto new_tuple = make_tuple(new_parameters.second, (new_parameters.second + new_parameters.first), population[i][j].job_id, 2);
				m1.push_back(new_tuple);
			}

			/*for (int t = 0; t < m1.size(); t++) {
				cout << t << endl;
				cout << "Zadanie " << get<2>(m1[t]) << "; Operacja " << get<3>(m1[t]) << "; Start: " << get<0>(m1[t]) << "; Koniec: " << get<1>(m1[t]) << endl;
				cout << "Zadanie " << get<2>(m2[t]) << "; Operacja " << get<3>(m2[t]) << "; Start: " << get<0>(m2[t]) << "; Koniec: " << get<1>(m2[t]) << endl << endl;
			}
			cout << "-----------------------------------------------" << endl << endl;*/
		}

		int sum = 0;

		for (int k = 0; k < m1.size(); k++) {
			sum += get<1>(m1[k]);
			sum += get<1>(m2[k]);
		}
		auto new_pair = make_pair(i, sum);
		fitness.push_back(new_pair);
	}

	int best_sum = numeric_limits<int>::max();

	if (the_best.second > 0)
		best_sum = the_best.second;

	for (int i = 0; i < fitness.size(); i++)
		if (best_sum > fitness[i].second) {
			best_sum = fitness[i].second;
			the_best = make_pair(population[fitness[i].first], best_sum);
		}

	return fitness;
}

vector<vector<Job>> select(vector<vector<Job>> population, vector<pair<int, int>> evaluation) {

	vector<vector<Job>> chosen;
	vector<pair<int, int>> fitness; // id, fitness_prob
	vector<pair<int, float>> fitness_norm; // id, fitness_norm
	vector<pair<int, float>> fitness_cumulative; // id, fitness_cumulative
	int chosen_size = (population.size()/2) + 1; // parametr do zmieniania

	sort(evaluation.rbegin(), evaluation.rend(), [](auto &left, auto &right) {
		return left.second < right.second;
	});

	for (int i = 0; i < evaluation.size(); i++) {
		auto new_pair = make_pair(evaluation[i].first, (i + 1));
		fitness.push_back(new_pair);
	}

	float sum = 0;

	for (int i = 0; i < fitness.size(); i++)
		sum += fitness[i].second;

	for (int i = 0; i < fitness.size(); i++) {
		auto new_pair = make_pair(fitness[i].first, (fitness[i].second / sum));
		fitness_norm.push_back(new_pair);
	}

	sort(fitness_norm.begin(), fitness_norm.end(), [](auto &left, auto &right) {
		return left.second < right.second;
	});

	for (int i = 0; i < fitness_norm.size(); i++) {
		if (i == 0) {
			auto new_pair = make_pair(fitness_norm[i].first, fitness_norm[i].second);
			fitness_cumulative.push_back(new_pair);
		}
		else {
			float sum = 0;
			for (int j = 0; j <= i; j++)
				sum += fitness_norm[j].second;
			auto new_pair = make_pair(fitness_norm[i].first, sum);
			fitness_cumulative.push_back(new_pair);
		}
	}
	
	vector<int> used;
	int index = 0;

	while(index < chosen_size) {
		float random = ((float)rand()) / (float)RAND_MAX;
		for (int k = 0; k < fitness_cumulative.size(); k++) {
			if (fitness_cumulative[k].second >= random) {
				if (find(used.begin(), used.end(), k) == used.end()) {
					chosen.push_back(population[fitness_cumulative[k].first]);
					used.push_back(k);
					index++;
					break;
				}
			}
		}
	}
	return chosen;
}

vector<vector<Job>> crossover(vector<vector<Job>> selected, int size_of_pop) {

	vector<vector<Job>> new_population;
	float cross_prob = 0.7; // parametr do zmieniania

	while (new_population.size() < size_of_pop) {

		int mother = rand() % selected.size();
		int father = rand() % selected.size();

		while(father == mother)
			father = rand() % selected.size();

		float random = ((float)rand()) / (float)RAND_MAX;

		if (random <= cross_prob) {

			int crosspoint = rand() % selected[mother].size();
			vector<Job> mother1, mother2;
			vector<Job> father1, father2;

			for (int i = 0; i < crosspoint; i++) {
				mother1.push_back(selected[mother][i]);
				father1.push_back(selected[father][i]);
			}

			for (int i = crosspoint; i < selected[mother].size(); i++) {
				mother2.push_back(selected[mother][i]);
				father2.push_back(selected[father][i]);
			}

			father2.insert(father2.end(), mother1.begin(), mother1.end());
			mother2.insert(mother2.end(), father1.begin(), father1.end());

			vector<Job> f2_doubles, m2_doubles, f2_missing, m2_missing;
			vector<int> f2_id, m2_id;

			for (int i = 0; i < father2.size(); i++) {
				for (int j = i + 1; j < father2.size(); j++) {
					if (father2[i].job_id == father2[j].job_id)
						f2_doubles.push_back(father2[i]);
				}
			}
			for (int i = 0; i < mother2.size(); i++) {
				for (int j = i + 1; j < mother2.size(); j++) {
					if (mother2[i].job_id == mother2[j].job_id)
						m2_doubles.push_back(mother2[i]);
				}
			}
			for (int i = 0; i < father2.size(); i++)
				f2_id.push_back(father2[i].job_id);
			for (int i = 0; i < mother2.size(); i++)
				m2_id.push_back(mother2[i].job_id);

			for (int i = 0; i < selected[father].size(); i++) {
				if (find(f2_id.begin(), f2_id.end(), selected[father][i].job_id) == f2_id.end())
					f2_missing.push_back(selected[father][i]);
			}
			for (int i = 0; i < selected[mother].size(); i++) {
				if (find(m2_id.begin(), m2_id.end(), selected[mother][i].job_id) == m2_id.end())
					m2_missing.push_back(selected[mother][i]);
			}

			for (int i = 0; i < f2_missing.size(); i++) {
				for (int j = 0; j < father2.size(); j++) {
					if (father2[j].job_id == f2_doubles[i].job_id) {
						father2[j] = f2_missing[i];
						break;
					}
				}
			}

			for (int i = 0; i < m2_missing.size(); i++) {
				for (int j = 0; j < mother2.size(); j++) {
					if (mother2[j].job_id == m2_doubles[i].job_id) {
						mother2[j] = m2_missing[i];
						break;
					}
				}
			}

			new_population.push_back(father2);
			new_population.push_back(mother2);
		}
		else {
			new_population.push_back(selected[mother]);
			new_population.push_back(selected[father]);
		}

	}

	return new_population;
}

vector<vector<Job>> mutate(vector<vector<Job>> population) {

	vector<vector<Job>> mutated_population = population;
	float mutation_prob = 0.05; // parametr do zmieniania

	for (int i = 0; i < mutated_population.size(); i++) {

		float random = ((float)rand()) / (float)RAND_MAX;

		if (random <= mutation_prob) {

			int pos1 = rand() % mutated_population[i].size();
			int pos2 = rand() % mutated_population[i].size();

			while (pos1 == pos2)
				pos2 = rand() % mutated_population[i].size();

			Job tmp = mutated_population[i][pos1];
			mutated_population[i][pos1] = mutated_population[i][pos2];
			mutated_population[i][pos2] = tmp;
		}
	}
	return mutated_population;
}

void write_to_file(pair<vector<Job>, int> the_best, pair<vector<Job>, int> random, vector<tuple<int, int, int, int>> maint1, int index) {
	
		// maint1 <nr_przerwy, nr_maszyny, czas trwania, czas startu>

		vector<tuple<int, int, int, int>> m1; // <start, koniec, job_id, op_id>
		vector<tuple<int, int, int, int>> m2; // <start, koniec, job_id, op_id>
		int readyt2 = 0;

		for (int j = 0; j < the_best.first.size(); j++) {
			if ((get<1>(the_best.first[j].op1)) == 1) {
				int new_start = check_others(m1, the_best.first[j], 1, readyt2);
				pair<int, int> new_parameters = check_maintenance(the_best.first[j], maint1, new_start, 1, readyt2); // czas, czas gotowoœci
				auto new_tuple = make_tuple(new_parameters.second, (new_parameters.second + new_parameters.first), the_best.first[j].job_id, 1);
				m1.push_back(new_tuple);
				readyt2 = new_parameters.second + new_parameters.first;
				new_start = check_others(m2, the_best.first[j], 2, readyt2);
				if (new_start == -1) {
					new_tuple = make_tuple(readyt2, (readyt2 + get<0>(the_best.first[j].op2)), the_best.first[j].job_id, 2);
					m2.push_back(new_tuple);
				}
				else {
					new_tuple = make_tuple(new_start, (new_start + get<0>(the_best.first[j].op2)), the_best.first[j].job_id, 2);
					m2.push_back(new_tuple);
				}

			}
			else {
				int new_start = check_others(m2, the_best.first[j], 1, readyt2);
				if (new_start == -1) {
					auto new_tuple = make_tuple((get<2>(the_best.first[j].op1)), (get<2>(the_best.first[j].op1) + get<0>(the_best.first[j].op1)), the_best.first[j].job_id, 1);
					readyt2 = (get<2>(the_best.first[j].op1) + get<0>(the_best.first[j].op1));
					m2.push_back(new_tuple);
				}
				else {
					auto new_tuple = make_tuple(new_start, (new_start + get<0>(the_best.first[j].op1)), the_best.first[j].job_id, 1);
					readyt2 = (new_start + get<0>(the_best.first[j].op1));
					m2.push_back(new_tuple);
				}
				new_start = check_others(m1, the_best.first[j], 2, readyt2);
				pair<int, int> new_parameters = check_maintenance(the_best.first[j], maint1, new_start, 2, readyt2);
				auto new_tuple = make_tuple(new_parameters.second, (new_parameters.second + new_parameters.first), the_best.first[j].job_id, 2);

				m1.push_back(new_tuple);
			}
		}

		/*for (int t = 0; t < m1.size(); t++) {
			cout << t << endl;
			cout << "Zadanie " << get<2>(m1[t]) << "; Operacja " << get<3>(m1[t]) << "; Start: " << get<0>(m1[t]) << "; Koniec: " << get<1>(m1[t]) << endl;
			cout << "Zadanie " << get<2>(m2[t]) << "; Operacja " << get<3>(m2[t]) << "; Start: " << get<0>(m2[t]) << "; Koniec: " << get<1>(m2[t]) << endl << endl;
		}
		cout << "-----------------------------------------------" << endl << endl;*/

		vector<tuple<int, int, string>> m1_and_maint1; // start, koniec, nazwa elementu

		// maint1 <nr_przerwy, nr_maszyny, czas trwania, czas startu>

		for (int i = 0; i < m1.size(); i++) {
			string name = "o";
			name.append(to_string(get<3>(m1[i])));
			name.append("_");
			name.append(to_string(get<2>(m1[i])));
			auto new_tuple = make_tuple(get<0>(m1[i]), get<1>(m1[i]), name);
			m1_and_maint1.push_back(new_tuple);
		}

		sort(maint1.begin(), maint1.end(), [](auto const &left, auto const &right) {
			return get<3>(left) < get<3>(right);
		});

		for (int i = 0; i < maint1.size(); i++) {
			string name = "maint";
			name.append(to_string(i + 1));
			name.append("_M1");
			auto new_tuple = make_tuple(get<3>(maint1[i]), (get<3>(maint1[i]) + get<2>(maint1[i])), name);
			m1_and_maint1.push_back(new_tuple);
		}
		sort(m1_and_maint1.begin(), m1_and_maint1.end(), [](auto const &left, auto const &right) {
			return get<0>(left) < get<0>(right);
		});

		vector<tuple<int, int, string>> idle1, idle2; // start, koniec, nazwa elementu
		vector<tuple<int, int, string>> m2_out; // start, koniec, nazwa elementu
		int counter = 1;

		for (int i = 0; i < m1_and_maint1.size(); i++) {
			int diff;
			int j = i + 1;
			if (j < m1_and_maint1.size()) {
				diff = get<0>(m1_and_maint1[j]) - get<1>(m1_and_maint1[i]);
				if (diff > 0) {
					string name = "idle";
					name.append(to_string(counter));
					name.append("_M1");
					auto new_tuple = make_tuple(get<1>(m1_and_maint1[i]), get<0>(m1_and_maint1[j]), name);
					idle1.push_back(new_tuple);
					counter++;
				}
			}
		}
		m1_and_maint1.insert(m1_and_maint1.end(), idle1.begin(), idle1.end());
		sort(m1_and_maint1.begin(), m1_and_maint1.end(), [](auto const &left, auto const &right) {
			return get<0>(left) < get<0>(right);
		});
		counter = 1;
		for (int i = 0; i < m2.size(); i++) {
			int diff;
			int j = i + 1;
			if (j < m2.size()) {
				diff = get<0>(m2[j]) - get<1>(m2[i]);
				if (diff > 0) {
					string name = "idle";
					name.append(to_string(counter));
					name.append("_M2");
					auto new_tuple = make_tuple(get<1>(m2[i]), get<0>(m2[j]), name);
					idle2.push_back(new_tuple);
					counter++;
				}
			}
		}

		for (int i = 0; i < m2.size(); i++) {
			string name = "o";
			name.append(to_string(get<3>(m2[i])));
			name.append("_");
			name.append(to_string(get<2>(m2[i])));
			auto new_tuple = make_tuple(get<0>(m2[i]), get<1>(m2[i]), name);
			m2_out.push_back(new_tuple);
		}
		m2_out.insert(m2_out.end(), idle2.begin(), idle2.end());
		sort(m2_out.begin(), m2_out.end(), [](auto const &left, auto const &right) {
			return get<0>(left) < get<0>(right);
		});

		string filename = "ins_out_";
		filename.append(to_string(index));
		filename.append(".txt");
		ofstream f(filename);

		f << filename << endl;
		f << the_best.second << ";" << random.second << endl;
		f << "M1: ";

		for (int i = 0; i < m1_and_maint1.size(); i++)
			f << get<2>(m1_and_maint1[i]) << "," << get<0>(m1_and_maint1[i]) << "," << (get<1>(m1_and_maint1[i]) - get<0>(m1_and_maint1[i])) << ";";
		f << endl;
		f << "M2: ";

		for (int i = 0; i < m2_out.size(); i++)
			f << get<2>(m2_out[i]) << "," << get<0>(m2_out[i]) << "," << (get<1>(m2_out[i]) - get<0>(m2_out[i])) << ";";
		f << endl;

		int sum = 0;

		for (int i = 0; i < maint1.size(); i++)
			sum += get<2>(maint1[i]);
		f << maint1.size() << "," << sum << endl;
		f << 0 << "," << 0 << endl;
		sum = 0;

		for (int i = 0; i < idle1.size(); i++) {
			int length = get<1>(idle1[i]) - get<0>(idle1[i]);
			sum += length;
		}
		f << idle1.size() << "," << sum << endl;
		sum = 0;

		for (int i = 0; i < idle2.size(); i++) {
			int length = get<1>(idle2[i]) - get<0>(idle2[i]);
			sum += length;
		}
		f << idle2.size() << "," << sum;
		f.close();
}

void generator(int i) {

	int jobs;
	vector<tuple<int, int, int, int>> times;
	vector<int> ready_times;
	vector<tuple<int, int, int, int>> maintenance;

	jobs = rand() % (51 - 10) + 10;

	int option = rand() % (4 - 1) + 1;

	if (option == 1) {

		for (int i = 0; i < jobs; i++) {


			int time_1 = rand() % (21 - 1) + 1;
			int time_2 = rand() % (21 - 1) + 1;

			int mach = rand() % (3 - 1) + 1;

			if (mach == 1) {

				int mach_1 = 1;
				int mach_2 = 2;
				auto job = make_tuple(time_1, time_2, mach_1, mach_2);
				times.push_back(job);
			}
			else {

				int mach_1 = 2;
				int mach_2 = 1;
				auto job = make_tuple(time_1, time_2, mach_1, mach_2);
				times.push_back(job);
			}

		}
	}
	else if (option == 2) {

		for (int i = 0; i < jobs; i++) {

			int time_1 = rand() % (201 - 1) + 1;
			int time_2 = rand() % (201 - 1) + 1;

			int mach = rand() % (3 - 1) + 1;

			if (mach == 1) {

				int mach_1 = 1;
				int mach_2 = 2;
				auto job = make_tuple(time_1, time_2, mach_1, mach_2);
				times.push_back(job);
			}
			else {

				int mach_1 = 2;
				int mach_2 = 1;
				auto job = make_tuple(time_1, time_2, mach_1, mach_2);
				times.push_back(job);
			}

		}
	}
	else {

		for (int i = 0; i < jobs; i++) {

			if (i % 2 == 0) {

				int time_1 = rand() % (21 - 1) + 1;
				int time_2 = rand() % (21 - 1) + 1;

				int mach = rand() % (3 - 1) + 1;

				if (mach == 1) {

					int mach_1 = 1;
					int mach_2 = 2;
					auto job = make_tuple(time_1, time_2, mach_1, mach_2);
					times.push_back(job);
				}
				else {

					int mach_1 = 2;
					int mach_2 = 1;
					auto job = make_tuple(time_1, time_2, mach_1, mach_2);
					times.push_back(job);
				}
			}
			else {
				int time_1 = rand() % (201 - 1) + 1;
				int time_2 = rand() % (201 - 1) + 1;

				int mach = rand() % (3 - 1) + 1;

				if (mach == 1) {
					int mach_1 = 1;
					int mach_2 = 2;
					auto job = make_tuple(time_1, time_2, mach_1, mach_2);
					times.push_back(job);
				}
				else {
					int mach_1 = 2;
					int mach_2 = 1;
					auto job = make_tuple(time_1, time_2, mach_1, mach_2);
					times.push_back(job);
				}
			}
		}
	}

	int sum = 0;

	for (int i = 0; i < times.size(); i++) {
		int tmp = get<0>(times[i]) + get<1>(times[i]);
		sum += tmp;
	}

	int threshold = sum / 4;

	for (int i = 0; i < times.size(); i++) {
		if (i % 2 == 0) {

			ready_times.push_back(0);
		}
		else {
			int ready = rand() % threshold;
			ready_times.push_back(ready);
		}
	}

	int threshold_maint = jobs / 5 + 1;
	int n_maint = rand() % (jobs - threshold_maint) + threshold_maint;

	for (int i = 0; i < n_maint; i++) {

		while (true) {

			int indicator = 0;

			int start = rand() % sum;
			int length = rand() % (51 - 2) + 2;
			int end = start + length;

			for (int j = 0; j < i; j++) {
				if (((start >= get<3>(maintenance[j]) && start <= (get<3>(maintenance[j]) + get<2>(maintenance[j]))) || (end >= get<3>(maintenance[j]) && end <= (get<3>(maintenance[j]) + get<2>(maintenance[j]))))) {
					indicator = 1;
					break;
				}
			}

			if (indicator == 0) {

				auto maint = make_tuple(i, 1, length, start);
				maintenance.push_back(maint);
				break;
			}

		}
	}

	string s_i = to_string(i);
	string filename = "ins_in_";
	filename.append(s_i);
	filename.append(".txt");
	ofstream f(filename);

	f << jobs << endl;

	for (int i = 0; i < times.size(); i++)
		f << get<0>(times[i]) << ";" << get<1>(times[i]) << ";" << get<2>(times[i]) << ";" << get<3>(times[i]) << ";" << ready_times[i] << ";" << endl;

	for (int i = 0; i < maintenance.size(); i++)
		f << get<0>(maintenance[i]) << ";" << get<1>(maintenance[i]) << ";" << get<2>(maintenance[i]) << ";" << get<3>(maintenance[i]) << endl;

	f.close();
}

void show(vector<tuple<int, int, int, int>> maint1) {

	for (int i = 0; i < maint1.size(); i++)
		cout << get<0>(maint1[i]) << " " << get<1>(maint1[i]) << " " << get<2>(maint1[i]) << " " << get<3>(maint1[i]) << endl;
}

void show(vector<Job> jobs) {

	for (int i = 0; i < jobs.size(); i++) {

		cout << "Zadanie " << jobs[i].job_id << endl;
		cout << "Operacja 1: " << get<0>(jobs[i].op1) << " " << get<1>(jobs[i].op1) << " " << get<2>(jobs[i].op1) << endl;
		cout << "Operacja 2: " << jobs[i].op2.first << " " << jobs[i].op2.second << endl << endl;
	}
}

int main()
{
	srand(time(0));
	cout.precision(2);
	cout.setf(ios::fixed);

	// parametry: generations = 100, size_of_pop = 100, chosen_size = pop/2 + 1, cross_prob = 0.7, mutation_prob = 0.05

	vector<tuple<int, int, int, int>> maint1; // <nr_przerwy, nr_maszyny, czas trwania, czas startu>
	int size_of_pop = 100; // parametr do zmieniania
	int generations = 100; // parametr do zmieniania

	for (int i = 1; i <= 50; i++) {
		vector<Job> jobs = read_from_file(i, maint1);
		vector<vector<Job>> population = initialize_population(jobs, size_of_pop);
		pair<vector<Job>, int> the_best;
		pair<vector<Job>, int> random;
		vector<pair<int, int>> evaluation = decode_and_evaluate(population, maint1, random);

		double time_;
		clock_t start, finish;

		start = clock();
		for (int i = 0; i < generations; i++) {
			vector<pair<int, int>> evaluation = decode_and_evaluate(population, maint1, the_best);
			vector<vector<Job>> selected = select(population, evaluation);
			vector<vector<Job>> new_population = crossover(selected, size_of_pop);
			vector<vector<Job>> mutated_population = mutate(new_population);
			vector<pair<int, int>> new_evaluation = decode_and_evaluate(mutated_population, maint1, the_best);
		}
		finish = clock();
		time_ = (finish - start) / (double)CLOCKS_PER_SEC;
		if (time_ >= 60) {
			time_ /= (double)60;
			cout << endl << endl << "Czas wykonania sie algorytmu: " << time_ << " minut." << endl << endl;
		}else
			cout << endl << endl << "Czas wykonania sie algorytmu: " << time_ << " sekund." << endl << endl;

		for (int i = 0; i < the_best.first.size(); i++)
			cout << the_best.first[i].job_id << " ";
		cout << the_best.second << endl << endl;
		write_to_file(the_best, random, maint1, i);
		maint1.clear();
	}
	cout << endl << endl << "\a\a\a\a\a";
	system("PAUSE");
	return 0;
}