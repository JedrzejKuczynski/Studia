#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

const int SIZE = 10000;

void selection_sort(int tab[])
{
    int tmp;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i+1; j < SIZE; j++)
        if (tab[j] < tab[i]){
            tmp = tab[j];
            tab[j] = tab[i];
            tab[i] = tmp;
            }

    }
}

void wyswietl(int tab []){

    for(int i = 0; i < SIZE; i++){

        cout << tab[i] << " ";
    }
}

void losowo(int tab[]){

    for(int i = 0; i < SIZE; i++){

        tab[i] = rand() % 100;
    }
}

void rosnaco(int tab[]){

    for(int i = 0; i < SIZE; i++){

        tab[i] = 2*i;
    }
}

void malejaco(int tab[]){

for(int i = 0; i < SIZE; i++){

        tab[i] = 10000 - 2 * i;
    }
}

void stala(int tab[]){

    for(int i = 0; i < SIZE; i++){

        tab[i] = 21;
    }
}

void a_kszt(int tab[]){

    for(int i = 0; i <= (SIZE - 1)/2; i++){

        tab[i] = 2 * i;
    }

    for(int i = SIZE/2; i < SIZE; i++){

        tab[i] = 10000 - 2 * i;
    }
}

int main()
{

    int tab[SIZE] = {0};
    double czas;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start, koniec;
    srand (time(NULL));

    a_kszt(tab);

    wyswietl(tab);

    start = clock();
    selection_sort(tab);
    koniec = clock();

    cout << endl << endl;

    czas = (koniec-start)/(double)CLOCKS_PER_SEC;

    wyswietl(tab);

    cout << endl << endl <<  "Czas wykonania:" << czas;
}


