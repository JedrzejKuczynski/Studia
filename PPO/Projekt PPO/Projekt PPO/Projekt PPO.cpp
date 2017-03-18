// ConsoleApplication7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string.h>
#include <fstream>

using namespace std;

ofstream ff;

class Record {

public:

	char *id;
	virtual ostream& wypisz(ostream& out) = 0;
	virtual void toText() = 0;

protected:

	Record(char *a) {

		id = a;
	}

};

ostream& operator<< (ostream& out, Record *r) {

	return r->wypisz(out);
}

class CoordinateRecord : public Record {

protected:

	CoordinateRecord(char *a) : Record(a) {}
};

class ModelRecord : public CoordinateRecord {

private:

	int serial;

public:

	ModelRecord(int a) :serial(a), CoordinateRecord("MODEL ") {}

	ostream& wypisz(ostream& out) {

		out << id << "Serial: " << setw(4) << serial << endl;

		return out;
	}

	void toText() {

		ff << id << setw(4) << serial << endl;
	}

	~ModelRecord() {
		delete id;
	}

};

class EndModelRecord : public CoordinateRecord {

public:

	EndModelRecord():CoordinateRecord("ENDMDL") {}

	ostream& wypisz(ostream& out) {

		out << id << endl;

		return out;
	}

	void toText() {

		ff << id << endl;
	}

	~EndModelRecord() {
		delete id;
	}
};

class TerRecord : public CoordinateRecord {

private:

	int serial, seq;
	char *res, *chain, *ins;

public:

	TerRecord(int a, int b, char *c, char *d, char *e):serial(a), seq(b), res(_strdup(c)), chain(_strdup(d)), ins(_strdup(e)), CoordinateRecord("TER   "){}

	ostream& wypisz(ostream& out) {

		out << id << "Serial: " << setw(5) << serial << " Residue name: " << setw(3) << res << " Chain identifier: " << chain << " Residue sequence number: " << setw(4) << seq << " Insertion code: " << ins << endl;

		return out;
	}

	void toText() {

		ff << id << setw(5) << serial << "      " << setw(3) << res << " " << chain << setw(4) << seq << ins << endl;
	}

	~TerRecord() {
		delete id;
		delete res;
		delete chain;
		delete ins;
	}
};

class HeterogenRecord : public Record {

protected:

	HeterogenRecord(char *a): Record(a){}
};

class HetRecord : public HeterogenRecord {

private:

	int seq, atoms;
	char *het, *chain, *ins, *text;

public:

	HetRecord(int a, int b, char *c, char *d, char *e, char *f):seq(a), atoms(b), het(_strdup(c)), chain(_strdup(d)), ins(_strdup(e)), text(_strdup(f)), HeterogenRecord("HET   "){}

	ostream& wypisz(ostream& out) {

		out << id << "Het identifier: " << setw(3) << het << " Chain identifier: " << chain << " Sequence number: " << setw(4) << seq << " Insertion code: " << ins << " Number of atoms: " << setw(5) << atoms << " Description: " << setw(40) << text << endl;

		return out;
	}

	void toText() {

		ff << id << " " <<  setw(3) << het << "  " << chain <<  setw(4) << seq << ins << "  " << setw(5) << atoms << "     " << setw(40) << text << endl;
	}

	~HetRecord() {
		delete id;
		delete het;
		delete chain;
		delete ins;
		delete text;
	}
};

class HetNamRecord : public HeterogenRecord {

private:

	int continuation;
	char *het, *text;

public:

	HetNamRecord(int a, char *b, char *c): continuation(a), het(_strdup(b)), text(_strdup(c)), HeterogenRecord("HETNAM"){}

	ostream& wypisz(ostream& out) {

		out << id << " Continuation: " << setw(2) << continuation << " Het identifier: " << setw(3) << het << " Chemical name: " << setw(55) << text << endl;

		return out;
	}

	void toText() {

		ff << id << " " << setw(2) <<  continuation << "  " << setw(3) << het << setw(55) << text << endl;
	}

	~HetNamRecord() {
		delete id;
		delete het;
		delete text;
	}
};

class PDB {

private:

	Record *pdb [1000];

	void zapisz_pdb(Record *nowy) {

		pdb[index++] = nowy;
	}

public:

	int index = 0;

	void wypisz(int i) {

		cout << pdb[i] << endl;
	}

	void odczyt_mdl(char *buf, char *serial) {

		Record *aktualny = NULL;

		strncpy_s(serial, 5, &(buf[10]), 4);
		aktualny = new ModelRecord(atoi(serial));
		zapisz_pdb(aktualny);
	}

	void odczyt_endmdl() {

		Record *aktualny = NULL;

		aktualny = new EndModelRecord();
		zapisz_pdb(aktualny);
	}

	void odczyt_ter(char *buf, char *serial, char *seq, char *res, char *chain, char *ins) {

		Record *aktualny = NULL;

		strncpy_s(serial, 6, &(buf[6]), 5);
		strncpy_s(seq, 5, &(buf[22]), 4);
		strncpy_s(res, 4, &(buf[17]), 3);
		strncpy_s(chain, 2, &(buf[21]), 1);
		strncpy_s(ins, 2, &(buf[26]), 1);
		aktualny = new TerRecord(atoi(serial), atoi(seq), res, chain, ins);
		zapisz_pdb(aktualny);
	}

	void odczyt_het(char *buf, char *het, char *chain, char *seq, char *ins, char *atoms, char *text) {

		Record *aktualny = NULL;

		strncpy_s(het, 4, &(buf[7]), 3);
		strncpy_s(chain, 2, &(buf[12]), 1);
		strncpy_s(seq, 5, &(buf[13]), 4);
		strncpy_s(ins, 2, &(buf[17]), 1);
		strncpy_s(atoms, 6, &(buf[20]), 5);
		strncpy_s(text, 40, &(buf[30]), 39);
		aktualny = new HetRecord(atoi(seq), atoi(atoms), het, chain, ins, text);
		zapisz_pdb(aktualny);
	}

	void odczyt_hetnam(char *buf, char *continuation, char *hetnam, char *chem) {

		Record *aktualny = NULL;

		strncpy_s(continuation, 3, &(buf[8]), 2);
		strncpy_s(hetnam, 4, &(buf[11]), 3);
		strncpy_s(chem, 55, &(buf[15]), 54);
		aktualny = new HetNamRecord(atoi(continuation), hetnam, chem);
		zapisz_pdb(aktualny);
	}

	void toText() {

		for (int i = 0; i < index; i++) {

			pdb[i]->toText();
		}
	}

	~PDB(){}
};

int _tmain(int argc, _TCHAR* argv[])
{
	PDB PDB;
	char buf[1000], serial[6], seq[5], res[4], chain[2], ins[2];
	char text[40];
	char chem[55], continuation[3];
		
	FILE *f;
	fopen_s(&f, "PDB.txt", "r");

	if (f != NULL) {

		cout << "Plik zostal otwarty! Nastepuje wczytanie linii MODEL, ENDMDL, TER, HET, HETNAM!" << endl << endl;

		while (!feof(f)) {

			if (fgets(buf, 1000, f)){

				if (!strncmp(buf, "MODEL ", 6))
					PDB.odczyt_mdl(buf, serial);
				else if (!strncmp(buf, "ENDMDL", 6))
					PDB.odczyt_endmdl();
				else if (!strncmp(buf, "TER   ", 6))
					PDB.odczyt_ter(buf, serial, seq, res, chain, ins);
				else if (!strncmp(buf, "HET   ", 6))
					PDB.odczyt_het(buf, res, chain, seq, ins, serial, text);
				else if (!strncmp(buf, "HETNAM", 6))
					PDB.odczyt_hetnam(buf, continuation, res, chem);
			}
		}
	}
	else
		cout << "Nie udalo sie otworzyc pliku!" << endl << endl;

	fclose(f);
	cout << "Plik zamknieto!" << endl << endl;

	cout << "Wczytane linie to:" << endl << endl;

	for (int i = 0; i < PDB.index; i++)
		PDB.wypisz(i);

	ff.open("PDB1.txt");

	if (ff.is_open()) {
		cout << "Udalo sie utworzyc plik PDB.txt! Nastepuje zapis wczytanych linii!" << endl << endl;
		PDB.toText();
	}
	else
		cout << "Nie udalo sie utworzyc pliku PDB.txt!" << endl << endl;

	ff.close();
	cout << "Zamknieto plik PDB.txt!" << endl << endl;

	system("PAUSE");
	return 0;
}

