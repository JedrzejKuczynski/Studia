#include <iostream>
#include <iomanip>
#include <cstdlib>


using namespace std;

const char BIALY = 0;
const char SZARY = 1;
const char CZARNY = 2;

class Kolejka{

public:

    int v;
    Kolejka *next;
};

class Graf{

    int V, index;
    int **macierz, *stos;
    char *odwiedziny;

public:

    Graf(int v){

        V = v;
        macierz = new int *[V];

        for(int i = 0; i < V; i++){
            macierz[i] = new int [V];
            for(int j = 0; j < V; j++)
                macierz[i][j] = 0;
        }

        for(int i = 0; i < V; i++){
            for(int j = 1; j < V; j++){
                if(i < j)
                    macierz[i][j] = 1;
        }
    }

        stos = new int [V];
        index = 0;

        odwiedziny = new char [V];

        for(int u = 0; u < V; u++)
            odwiedziny[u] = BIALY;

    }

    void DFS(){

        for(int u = 0; u < V; u++){
            if(odwiedziny[u] == BIALY)
                DFS_Visit(u);
        }

    }

    void DFS_Visit(int u){

        odwiedziny[u] = SZARY;

        for(int v = 0; v < V; v++){
            if((macierz[u][v] == 1) && odwiedziny[v] == BIALY)
                DFS_Visit(v);
        }

        odwiedziny[u] = CZARNY;
        stos[index++] = u;
    }

    void BFS(int s){

        odwiedziny[s] = SZARY;

        Kolejka *w, *head, *tail;

        w = new Kolejka;
        w->next = NULL;
        w->v = s;
        head = tail = w;

        while(head != NULL){

            s = head->v;
            w = head;
            head = head->next;

            if(head == NULL)
                tail = NULL;
            delete w;

            cout << s << " ";

            for(int i = 0; i < V; i++){
                if((macierz[s][i] == 1) && odwiedziny[i] == BIALY){

                    odwiedziny[i] = SZARY;

                    w = new Kolejka;
                    w->next = NULL;
                    w->v = i;

                    if(tail == NULL)
                        head = w;
                    else
                        tail->next = w;
                    tail = w;
                }
            }

            odwiedziny[s] = CZARNY;
        }
    }

    void wypisz(){

        cout << "   ";
        for(int i = 0; i < V; i++)
            cout << setw(3) << i;

        cout << endl << endl;

        for(int i = 0; i < V; i++){
            cout << setw(3) << i;
            for(int j = 0; j < V; j++)
                cout << setw(3) << macierz[i][j];
            cout << endl;
        }
    }

    void wypisz_DFS(){

        for(int i = V - 1; i >= 0;i--)
            cout << stos[i] << " ";
    }

    ~Graf(){

        for(int i = 0; i < V; i++)
            delete[] macierz[i];
        delete[] macierz;
        delete[] odwiedziny;
        delete[] stos;
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
    cout << endl << endl;
    g.BFS(0);
    cout << endl;

    return 0;
}
