#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//const int SIZE = 20;

void heap_sort(int *tab, int SIZE, int x);
void heapify(int *tab, int SIZE, int x);

void build_heap (int *tab, int SIZE)
{
int i;
for (i = (SIZE-1)/2; i >= 0; i--)
heapify(tab, SIZE, i);
}

void heapify(int *tab, int SIZE, int x)
{
    int l, r, tmp, i;
    l = 2*x;
    r= (2*x)+1;

    do {
        if ( r <= SIZE)
        {
            if(tab[r] < tab[l])
                i = l;
            else i= r;
        }
            else i = l;
    if (tab[i] > tab[x])
            {tmp = tab[i];
            tab[i] = tab[x];
            tab[x] = tmp;
            x=i;
            l = 2*x;
            r= (2*x)+1;}
    else
        break;
    }
    while ( l <= SIZE);
}

void heap_sort(int *tab, int SIZE)
{
int temp;
build_heap(tab, SIZE);
for (int i=SIZE - 1; i>0; i--)
{
    temp=tab[i];
    tab[i]=tab[0];
    tab[0]=temp;
    SIZE--;
    heapify(tab, i - 1, 0);
}
}

void wyswietl(int *tab , int SIZE){

    for(int i = 0; i < SIZE; i++){

        cout << tab[i] << " ";
    }
}

void losowo(int *tab, int SIZE){

    for(int i = 0; i < SIZE; i++){

        tab[i] = rand() % 100;
    }
}

void rosnaco(int *tab, int SIZE){

    for(int i = 0; i < SIZE; i++){

        tab[i] = 2*i;
    }
}

void malejaco(int *tab, int SIZE){

for(int i = 0; i < SIZE; i++){

        tab[i] = 10000 - 2 * i;
    }
}

void stala(int *tab, int SIZE){

    for(int i = 0; i < SIZE; i++){

        tab[i] = 21;
    }
}

void a_kszt(int *tab, int SIZE){

    for(int i = 0; i <= (SIZE - 1)/2; i++){

        tab[i] = 2 * i;
    }

    for(int i = SIZE/2; i < SIZE; i++){

        tab[i] = 10000 - 2 * i;
    }
}

int main()
{
    int SIZE;
    cout << "Podaj ilosc elementow: " << endl;
    cin >> SIZE;
    cout << endl ;
    int *tab = new int[SIZE];
    double czas;
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t start, koniec;
    srand (time(NULL));

    malejaco(tab, SIZE);

    wyswietl(tab, SIZE);

    start = clock();
    heap_sort(tab, SIZE);
    koniec = clock();

    cout << endl << endl;

    czas = (koniec-start)/(double)CLOCKS_PER_SEC;

    cout << endl << endl;

    wyswietl(tab, SIZE);

    cout << endl << endl <<  "Czas wykonania:" << czas << endl;
}


