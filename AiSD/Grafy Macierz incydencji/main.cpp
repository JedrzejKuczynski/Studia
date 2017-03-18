#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Graf{

    int V;

    int **macierz;

public:

    Graf(int v){

        V = v;
        macierz = new int *[V];

        for(int i = 0; i < V; i++){
            macierz[i] = new int [(V*V - V)/2];
            for(int j = 0; j < (V*V - V)/2; j++)
                macierz[i][j] = 0;
        }

        for(int i = 0; i < V; i++){
            for(int j = 0; j < V - 1; j++){
                macierz[i][j] = 1;
        }

    }
    }


    void wypisz(){

        cout << "   ";
        for(int i = 0; i < (V*V - V)/2; i++)
            cout << setw(3) << i;

        cout << endl << endl;

        for(int i = 0; i < V; i++){
            cout << setw(3) << i;
            for(int j = 0; j < (V*V - V)/2; j++)
                cout << setw(3) << macierz[i][j];
            cout << endl;
        }
    }
};

int main()
{

    int v;

    cout << "Podaj, ile wierzcholkow ma miec graf: ";
    cin >> v;

    Graf g(v);
    cout << endl << endl;
    g.wypisz();

    return 0;
}
