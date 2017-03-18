#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

const int SIZE = 1000;

void shell_sort(int tab[]){

    int tmp, gap;

    for (gap = SIZE/2; gap > 0; gap /= 2)
        for (int i = gap; i < SIZE; i++)
            for (int j = i - gap; j >= 0 && tab[j] > tab[j+gap]; j -= gap){

                tmp = tab[j];
                tab[j] = tab[j+gap];
                tab[j+gap] = tmp;
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
    shell_sort(tab);
    koniec = clock();

    czas = (koniec - start)/(double)CLOCKS_PER_SEC;

    wyswietl(tab);

    cout << endl << endl << "Czas wykonania: " << czas << endl;
}



