#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

class Graph {

	public:

		class Vertex {

		public:

			string seq_id;
			string seq;
			int v_id, degree;
			pair<int, int> position;
			vector<int> quality;

			Vertex() {}

			Vertex(string tmp_id, string tmp_seq, int window, vector<int> tmp_quality, int i) {

				int end = i + window - 1;

				seq_id = tmp_id;
				seq = tmp_seq.substr(i, window);
				v_id = i;
				degree = 0;
				position = make_pair(i, end);

				for (i; i < end; i++)
					quality.push_back(tmp_quality[i]);
			}
		};

public:

	Graph(string name, int window, int cred) {

		credibility = cred;

		string qual_name = name;
		qual_name.append("_qual.txt");
		name.append("_fasta.txt");

		ifstream fasta(name);
		ifstream qual(qual_name);

		if (fasta.good() && qual.good()) {

			while ((!fasta.eof()) && (!qual.eof())) {

				string tmp_seq, tmp_id;
				vector<int> tmp_quality;
				string tmp;
				int value;

				getline(fasta, tmp, '\n');
				tmp_id = tmp.substr(0, 15);
				getline(fasta, tmp, '\n');
				tmp_seq.append(tmp);
				getline(fasta, tmp, '\n');
				tmp_seq.append(tmp);

				sequences.push_back(make_pair(tmp_id, tmp_seq));

				getline(qual, tmp, '\n');
				int loop = 0;

				while (getline(qual, tmp)) {

					istringstream is(tmp);

					while (is >> value)
						tmp_quality.push_back(value);

					loop++;
					if (loop >= 2)
						break;
				}

				int end = tmp_seq.size() - window;

				for (int i = 0; i <= end; i++) {
					Vertex v_new = Vertex::Vertex(tmp_id, tmp_seq, window, tmp_quality, i);
					vertices.push_back(v_new);
				}
			}

			fasta.close();
			qual.close();
		}
		else
			cout << "Nie udalo sie otworzyc plikow!" << endl << endl;

		int size = vertices.size();

		matrix.resize(size);

		for (int i = 0; i < size; i++)
				matrix[i].resize(size);

		for (int i = 0; i < vertices.size(); i++) {
			for (int j = i + 1; j < vertices.size(); j++) {
				if (vertices[i].seq_id != vertices[j].seq_id) {
					if (vertices[i].seq == vertices[j].seq) {
						matrix[i][j] = 1;
						matrix[j][i] = 1;
						vertices[i].degree++;
						vertices[j].degree++;
					}
					else if (vertices[i].seq != vertices[j].seq) {
						string tmp = vertices[i].seq;
						int counter = 0;
						for (int k = 0; k < vertices[i].quality.size(); k++) {
							if (vertices[i].quality[k] < credibility) {
								tmp.erase(counter, 1);
							}else
								counter++;
						}
							int threshold = window / 2;
							if (tmp.size() > threshold) {
								int end = window - tmp.size();
								for (int l = 0; l <= end; l++) {
									if (tmp == vertices[j].seq.substr(l, tmp.size())) {
										matrix[i][j] = 1;
										matrix[j][i] = 1;
										vertices[i].degree++;
										vertices[j].degree++;
									}
								}
						}
					}
				}
			}
		}
	}

	void show_vertices() {

		for (int i = 0; i < vertices.size(); i++) {
			cout << vertices[i].seq_id << "; " << vertices[i].seq << "; " << vertices[i].v_id << "; <" << vertices[i].position.first << ";" << vertices[i].position.second << "> ";
			for (int j = 0; j < vertices[i].quality.size(); j++)
				cout << vertices[i].quality[j] << " ";
			cout << endl << endl;
		}
	}

	void show_sequences() {

		for (int i = 0; i < sequences.size() - 1; i++)
			cout << sequences[i].first << " " << sequences[i].second << endl << endl;
	}

	void show_matrix() {

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

	void show_clique() {

		for (int i = 0; i < max_clique_found.size(); i++)
			cout << max_clique_found[i] << " ";
	}

	void show_clique_series() {

		for (int i = 0; i < max_clique_series.size(); i++)
			cout << "Dla sekwencji o identyfikatorze: " << get<0>(max_clique_series[i]) << " na pozycji od " << setw(3) << get<1>(max_clique_series[i]) + 1 <<
			" do " << setw(3) <<  get<2>(max_clique_series[i]) << " znaleziono motyw o sekwencji: " << get<3>(max_clique_series[i]) << endl << endl;
	}

	vector<int> find_neighbours(int v) {

		vector<int> neighbours;

		for (int i = 0; i < matrix.size(); i++)
			if (matrix[v][i] == 1)
				neighbours.push_back(i);

		return neighbours;

	}

	vector<int> find_max_neighbours(int v, int max) {

		vector<int> max_neighbours;

		for (int i = 0; i < matrix.size(); i++)
			if (matrix[v][i] == 1 && vertices[i].degree >= max)
				max_neighbours.push_back(i);

		return max_neighbours;
	}

	vector<int> find_shared_neighbours(vector<int> pruned_neighbours, vector<int> neighbours_of_vmax) {

		vector<int> intersection;

		sort(pruned_neighbours.begin(), pruned_neighbours.end());
		sort(neighbours_of_vmax.begin(), neighbours_of_vmax.end());

		set_intersection(pruned_neighbours.begin(), pruned_neighbours.end(), neighbours_of_vmax.begin(), neighbours_of_vmax.end(), back_inserter(intersection));

		return intersection;
	}

	int find_max_v(vector<int> pruned_neighbours) {

		int max_degree = 0;
		int max_v = 0;

		for (int i = 0; i < pruned_neighbours.size(); i++) {
			if (vertices[pruned_neighbours[i]].degree > max_degree) {
				max_degree = vertices[pruned_neighbours[i]].degree;
				max_v = pruned_neighbours[i];
			}
		}

		return max_v;
	}

	vector<int>& clique_heur(vector<int> &candidate, vector<int> pruned_neighbours, int size, int max) {

		if (pruned_neighbours.empty()) {
			if (size > max)
				return candidate;
		}


		int v_max = find_max_v(pruned_neighbours);
		candidate.push_back(v_max);

		for (int i = 0; i < pruned_neighbours.size(); i++)
			if (pruned_neighbours[i] == v_max)
				pruned_neighbours.erase(pruned_neighbours.begin()+i);

		vector<int> neighbours_of_vmax = find_max_neighbours(v_max, max);
		vector<int> shared_neighbours = find_shared_neighbours(pruned_neighbours, neighbours_of_vmax);
		clique_heur(candidate, shared_neighbours, size + 1, max);

		return candidate;

	}

	void max_clique_heur(int max) {

		vector<int> candidate;

		for (int i = 0; i < matrix.size(); i++) {
			candidate.push_back(i);
			if (vertices[i].degree >= max) {
				vector<int> prunedneighbours_of_i;
				vector<int> neighbours_of_i = find_neighbours(i);

				for (int j = 0; j < neighbours_of_i.size(); j++) {
					int id = neighbours_of_i[j];
					if (vertices[id].degree >= max) {
						prunedneighbours_of_i.push_back(id);
					}
				}

				vector<int> current_clique = clique_heur(candidate, prunedneighbours_of_i, 1, max);

				if (current_clique.size() > max_clique_found.size())
					max_clique_found = current_clique;
			}
			candidate.clear();
		}
	}

	void go_left(vector<int> &left_clique) {

		for (int i = 0; i < left_clique.size(); i++)
			if (left_clique[i] <= 0)
				return;

		for (int i = 0; i < left_clique.size(); i++) {
			for (int j = i + 1; j < left_clique.size(); j++) {
				if (matrix[left_clique[i] - 1][left_clique[j] - 1] != 1)
					return;
			}
		}

		for (int i = 0; i < left_clique.size(); i++)
			left_clique[i]--;

		go_left(left_clique);

		return;
	}

	void go_right(vector<int> &right_clique) {

		for (int i = 0; i < right_clique.size(); i++)
			if (right_clique[i] >= matrix.size() - 1)
				return;

		for (int i = 0; i < right_clique.size(); i++) {
			for (int j = i + 1; j < right_clique.size(); j++) {
				if (matrix[right_clique[i] + 1][right_clique[j] + 1] != 1)
					return;
			}
		}

		for (int i = 0; i < right_clique.size(); i++)
			right_clique[i]++;

		go_right(right_clique);

		return;
	}

	string find_sequence(int id, int start, int end) {

		string seq, seq_id;

		seq_id = vertices[id].seq_id;

		for (int i = 0; i < sequences.size(); i++)
			if (seq_id == sequences[i].first)
				seq = sequences[i].second.substr(start, end + 1);

		return seq;
	}

	void clique_series() {

		vector<int> left_clique = max_clique_found;
		vector<int> right_clique = max_clique_found;
		vector<string> seq_ids;

		for (int i = 0; i < max_clique_found.size(); i++)
			seq_ids.push_back(vertices[max_clique_found[i]].seq_id);

		go_left(left_clique);
		go_right(right_clique);

		for (int i = 0; i < max_clique_found.size(); i++) {
			int start = vertices[left_clique[i]].position.first + 1;
			int end = vertices[right_clique[i]].position.second - vertices[left_clique[i]].position.first;
			string seq = find_sequence(max_clique_found[i], start, end);
			max_clique_series.push_back(make_tuple(seq_ids[i], start, start + seq.size(), seq));
		}
	}

private:

	int credibility;
	vector<vector<int>> matrix;
	vector<pair<string, string>> sequences;
	vector<Vertex> vertices;
	vector<int> max_clique_found;
	vector<tuple<string, int, int, string>> max_clique_series;
};

#endif