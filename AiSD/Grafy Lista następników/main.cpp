#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const char BIALY = 0;
const char SZARY = 1;
const char CZARNY = 2;

class Lista{

public:

    int v;
    Lista *next;
};

class Graf{

    int V, index;
    int *stos;
    char *odwiedziny;
    Lista **nastepstwa;

public:

    Graf(int v){

        V = v;
        nastepstwa = new Lista *[V];

        for(int i = 0; i < V; i++)
            nastepstwa[i] = NULL;

        for(int i = 0; i < V; i++){
            for(int j = 1; j < V; j++){
                if(i < j){

                Lista *nowy = new Lista;
                nowy->v = j;
                nowy->next = nastepstwa[i];
                nastepstwa[i] = nowy;
                }
            }
        }

        stos = new int [V];
        index = 0;

        odwiedziny = new char [V];

        for(int u = 0; u < V; u++)
            odwiedziny[u] = BIALY;
    }

    void DFS_Visit(int u){

        Lista *v;

        odwiedziny[u] = SZARY;

        for(v = nastepstwa[u]; v != NULL; v = v->next){
            if(odwiedziny[v->v] == BIALY)
                DFS_Visit(v->v);
        }

        odwiedziny[u] = CZARNY;
        stos[index++] = u;
    }

    void DFS(){

        for(int u = 0; u < V; u++){
            if(odwiedziny[u] == BIALY)
                DFS_Visit(u);
        }
    }

     void BFS(int s){

        odwiedziny[s] = SZARY;

        Lista *w, *head, *tail, *v;

        w = new Lista;
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

            stos[index++] = s;

            for(v = nastepstwa[s]; v != NULL; v = v->next){
                if(odwiedziny[v->v] == BIALY){

                    odwiedziny[v->v] = SZARY;

                    w = new Lista;
                    w->next = NULL;
                    w->v = v->v;

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

        for(int i = 0; i < V; i++){

            cout << "V[" << i << "] = ";
            Lista *nowy = new Lista;
            nowy = nastepstwa[i];

            while(nowy != NULL){

                cout << nowy->v << " ";
                nowy = nowy->next;
            }
            cout << endl;
        }
    }

    void wypisz_DFS(){

        for(int i = V - 1; i >= 0; i--)
            cout << stos[i] << " ";
    }

    void wypisz_BFS(){

        cout << stos[0] << " ";

        for(int i = V - 1; i > 0; i--)
            cout << stos[i] << " ";
    }

    ~Graf(){

        for(int i = 0; i < V; i++){

            Lista *nowy = new Lista;
            nowy = nastepstwa[i];

            while(nowy != NULL){

                Lista *tmp = new Lista;
                tmp = nowy;
                nowy = nowy->next;
                delete tmp;
            }
        }
        delete[] nastepstwa;
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
    g.wypisz_BFS();
    cout << endl;

    return 0;
}
