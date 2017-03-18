#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct lista{

    int wartosc;
    lista *next;
    lista *prev;
};

lista *l_head = NULL;
lista *l_ost = NULL;

void insertion_sort(int tab[], int rozmiar){

    int tmp;

    for(int i = 1; i < rozmiar; i++){

        while(i > 0 && tab[i - 1] > tab[i]){

            tmp = tab[i];

            tab[i] = tab[i - 1];
            tab[i - 1] = tmp;

            i--;
        }
    }
}

void sortuj_l(){


}



void l_tworz(int tab[], int rozmiar){

    int i = 0;


    while(i < rozmiar){
        if(l_head == NULL){

            l_head = new lista;
            l_head->next = NULL;
            l_head->prev = NULL;
            l_head->wartosc = tab[i];

            l_ost = l_head;

            i++;

        }else{

            lista *l = new lista;

            l_ost->next = l;
            l->prev = l_ost;
            l->next = NULL;
            l->wartosc = tab[i];

            l_ost = l;

            i++;

        }
    }
}



bool powt(int tab[], int wartosc, int rozmiar)
{
    for(int i = 0; i < rozmiar; i++)
    {
        if(tab[i] == wartosc)
             return false;

    }
    return true;
}

void wyswietl_t(int tab[], int rozmiar){

    for(int i = 0; i < rozmiar; i++){

        cout << tab[i] << " ";
    }

    cout << endl;
}

void wyswietl_l(int rozmiar){

    lista *tmp = l_head;
    cout << endl;

    if(tmp == NULL){
        cout << "Brak elementow" << endl;
    }else{
        while(tmp != NULL){

        cout << tmp->wartosc << " ";

        tmp = tmp->next;


        }
    }

    delete tmp;

}

void t_tab(int *tab, int rozmiar){

    int wartosc;

    for(int i = 0; i < rozmiar; i++){

        wartosc = rand() % 100000;
        if(powt(tab, wartosc, rozmiar))
            tab[i] = wartosc;
    }
}

void wyswietl_m(){

    cout << "Stworz tablice - wcisnij 0" << endl;
    cout << "Stworz posortowana liste - wcisnij 1" << endl;
    cout << "Stworz drzewo BST - wcisnij 2" << endl;
    cout << "Stworz drzewo AVL - wcisnij 3" << endl;

}

int opcja(){

    int wybor;

    while(1){

        cout << endl <<  "Wybierz opcje " << endl;

        if(cin >> wybor){
            cin.ignore();
            break;
        }
    }

    return wybor;
}

int main(){

    int *tab, rozmiar, menu;

    srand(time(NULL));
    wyswietl_m();

    while(1){

        menu = opcja();

        switch(menu){


            case 0:
                cout << "Podaj rozmiar tablicy." << endl;
                cin >> rozmiar;
                tab = new int [rozmiar];
                t_tab (tab, rozmiar);
                wyswietl_t(tab, rozmiar);
                break;

            case 1:
                //insertion_sort(tab, rozmiar);
                l_tworz(tab, rozmiar);
                sortuj_l();
                wyswietl_l(rozmiar);
                break;

        }
    }

    return 0;

}
