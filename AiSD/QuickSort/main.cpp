#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 400000;

void quick_sort(int tab[], int left, int right)
{
    int i = left;
    int j = right;
    int tmp;
    int x = tab[(i + j)/2];
    while (i <= j){
        while (tab[i] < x)
            i++;
        while (tab[j] > x)
            j--;
        if (i <= j){
            tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        quick_sort(tab, left, j);
    if (i < right)
        quick_sort(tab, i, right);
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

  //  wyswietl(tab);

    start = clock();
    quick_sort(tab, 0, SIZE-1);
    koniec = clock();

    cout << endl << endl;

    czas = (koniec-start)/(double)CLOCKS_PER_SEC;

    cout << endl << endl;

  //  wyswietl(tab);

    cout << endl << endl <<  "Czas wykonania:" << czas << endl;
}


