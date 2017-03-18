#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

const int SIZE = 10000;

void insertion_sort(int tab[]){

    int tmp;

    for(int i = 1; i < SIZE; i++){

        while(i > 0 && tab[i - 1] > tab[i]){

            tmp = tab[i];

            tab[i] = tab[i - 1];
            tab[i - 1] = tmp;

            i--;
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


    srand(time(NULL));

    losowo(tab);

    wyswietl(tab);

    cout << endl << endl;

    start = clock();
    insertion_sort(tab);
    koniec = clock();

    czas = (koniec - start)/(double)CLOCKS_PER_SEC;

    wyswietl(tab);

    cout << endl << endl << "Czas wykonania: " << czas << endl;
}



