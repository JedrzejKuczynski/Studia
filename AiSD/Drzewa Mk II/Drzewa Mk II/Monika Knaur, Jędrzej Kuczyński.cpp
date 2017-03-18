#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct bst_wezel{

    int wartosc;
    bst_wezel *left;
    bst_wezel *right;
    bst_wezel *parent;
};

bst_wezel *korzen = NULL;
bst_wezel *korzenol = NULL;

bool powt(int tab[], int rozmiar, int wartosc){

    for(int i = 0; i < rozmiar; i++){
        if(tab[i] == wartosc)
            return false;
    }
    return true;
}

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

bst_wezel *najmniejszy(bst_wezel *wezel){

    if(wezel->left != NULL)
        return najmniejszy(wezel->left);
    else
        return wezel;
}


void wyswietl_tab(int tab[], int rozmiar){

    for(int i = 0; i < rozmiar; i++){

        cout << tab[i] << " ";
    }

    cout << endl;
}

void t_tab(int *tab, int rozmiar, int r){

    for(int i = 0; i < rozmiar; i++){

		int wartosc = (rand()*rand())%(r - 1) + 1;

        if(powt(tab, rozmiar, wartosc)){
            tab[i] = wartosc;
        }
    }
}

void t_tabs(int *tab_s, int rozmiar){

    for(int i = 0; i < rozmiar; i++){

        tab_s[i] = i;
    }
}


void bst_drzewo(bst_wezel *wezel, int tab[]){

    static int i = 0;

    if(korzen == NULL){

        korzen = new bst_wezel;

        korzen->wartosc = tab[i];
        korzen->left = NULL;
        korzen->right = NULL;
        korzen->parent = NULL;

        i++;

    }else if(tab[i] < wezel->wartosc){
        if(wezel->left != NULL){
            bst_drzewo(wezel->left, tab);
        }else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = tab[i];
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->left = nowy;

            i++;
        }
    }else if(tab[i] > wezel->wartosc){
        if(wezel->right != NULL){
            bst_drzewo(wezel->right, tab);
        }else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = tab[i];
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->right = nowy;

            i++;
        }
    }
}

void bst_dodawanie(bst_wezel *wezel, int wartosc){

    if(korzen == NULL){

        korzen = new bst_wezel;

        korzen->wartosc = wartosc;
        korzen->left = NULL;
        korzen->right = NULL;
        korzen->parent = NULL;

    }else if(wartosc < wezel->wartosc)
        if(wezel->left != NULL)
            bst_dodawanie(wezel->left, wartosc);
        else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = wartosc;
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->left = nowy;
        }
    else if(wartosc >= wezel->wartosc){
        if(wezel->right != NULL){
            bst_dodawanie(wezel->right, wartosc);
        }else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = wartosc;
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->right = nowy;
        }
    }
}

void bst_drzewol(bst_wezel *wezel, int tab[]){

    static int j = 0;

    if(korzenol == NULL){

        korzenol = new bst_wezel;

        korzenol->wartosc = tab[j];
        korzenol->left = NULL;
        korzenol->right = NULL;
        korzenol->parent = NULL;

        j++;

    }else if(tab[j] < wezel->wartosc)
        if(wezel->left != NULL)
            bst_drzewol(wezel->left, tab);
        else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = tab[j];
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->left = nowy;

            j++;
        }
    else if(tab[j] > wezel->wartosc){
        if(wezel->right != NULL){
            bst_drzewol(wezel->right, tab);
        }else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = tab[j];
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->right = nowy;

            j++;
        }
    }
}

/*void bst_drzewo_avl(bst_wezel *wezel, unsigned int tab[]){

    static unsigned int k = 0;

    if(korzen_avl == NULL){

        korzen_avl = new bst_wezel;

        korzen_avl->wartosc = tab[k];
        korzen_avl->left = NULL;
        korzen_avl->right = NULL;
        korzen_avl->parent = NULL;

        k++;

    }else if(tab[k] < wezel->wartosc)
        if(wezel->left != NULL)
            bst_drzewo_avl(wezel->left, tab);
        else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = tab[k];
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->left = nowy;

            k++;

        }else if(tab[k] > wezel->wartosc){
			if(wezel->right != NULL){
				bst_drzewo_avl(wezel->right, tab);
			}else{
				bst_wezel *nowy = new bst_wezel;

				nowy->wartosc = tab[k];
				nowy->left = NULL;
				nowy->right = NULL;
				nowy->parent = wezel;
				wezel->right = nowy;

				k++;
        }
    }
}*/

void bst_drzewol(bst_wezel *wezel,int wartosc){

    if(korzenol == NULL){

        korzenol = new bst_wezel;

        korzenol->wartosc = wartosc;
        korzenol->left = NULL;
        korzenol->right = NULL;
        korzenol->parent = NULL;

    }else if(wartosc < wezel->wartosc)
        if(wezel->right != NULL)
            bst_drzewol(wezel->right, wartosc);
        else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = wartosc;
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->right = nowy;
        }
    else if(wartosc >= wezel->wartosc){
        if(wezel->right != NULL){
            bst_drzewol(wezel->right, wartosc);
        }else{
            bst_wezel *nowy = new bst_wezel;

            nowy->wartosc = wartosc;
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = wezel;
            wezel->right = nowy;
        }
    }
}


void bst_wycinka(bst_wezel *wezel){

    if(wezel != NULL){

        bst_wycinka(wezel->left);
        bst_wycinka(wezel->right);

        delete wezel;

    }
}

void bst_wycinkal(bst_wezel *wezel){

    if(wezel != NULL){
        bst_wycinkal(wezel->right);

        delete wezel;
    }
}

void wyswietl_drzewo(bst_wezel *wezel){

    if(wezel != NULL){

        wyswietl_drzewo(wezel->left);
        cout << wezel->wartosc << " ";
        wyswietl_drzewo(wezel->right);
    }
}


bst_wezel* wyszukaj(bst_wezel *wezel, int wartosc){

    if(wezel->wartosc == wartosc)
        return wezel;

    if(wartosc < wezel->wartosc && wezel->left != NULL)
        return wyszukaj(wezel->left, wartosc);
    else if(wartosc >= wezel->wartosc && wezel->right != NULL)
        return wyszukaj(wezel->right, wartosc);

    return NULL;

}

void bst_usun(bst_wezel *wezel){

    if(wezel == NULL)
        return;

    if(wezel->left == NULL && wezel->right == NULL){
        if(wezel->parent == NULL)
            korzen = NULL;
        else if(wezel->parent->left == wezel)
            wezel->parent->left = NULL;
        else if(wezel->parent->right == wezel)
            wezel->parent->right = NULL;

        delete wezel;
        }else if(wezel->left == NULL || wezel->right == NULL){
            if(wezel->left == NULL){
                if(wezel->parent == NULL)
                    korzen = wezel->right;
                else if(wezel->parent->left == wezel)
                    wezel->parent->left = wezel->right;
                else if(wezel->parent->right == wezel)
                    wezel->parent->right = wezel->right;
                }else{
                    if(wezel->parent == NULL)
                        korzen = wezel->left;
                    else if(wezel->parent->left == wezel)
                        wezel->parent->left = wezel->left;
                    else if(wezel->parent->right == wezel)
                        wezel->parent->right = wezel->left;
                    }
                delete wezel;
        }else{
            bst_wezel *tmp = najmniejszy(wezel->right);
            wezel->wartosc = tmp->wartosc;
            bst_usun(tmp);
        }
}

/*void bst_usunol(bst_wezel *wezel){

    if(wezel == NULL)
        return;

    if(wezel->right == NULL){
        delete wezel;
    }else{
        wezel->parent->right = wezel->right;
        delete wezel;
    }



}*/


void wyswietl_m(){

    cout << "Stworz drzewo BST - wcisnij 1" << endl;
    cout << "Stworz drzewo AVL - wcisnij 2" << endl;
    cout << "Stworz zdegenerowane drzewo BST - wcisnij 3" << endl;
    cout << "Wyszukaj losowo wybrane elementy w drzewie BST - wcisnij 4" << endl;
    cout << "Wyszukaj losowo wybrane elementy w zdegenerowanym drzewie BST - wcisnij 6" << endl;
    cout << "Wstaw element do drzewa BST (z koncowki tablicy poczatkowej) - wcisnij 7" << endl;
    cout << "Wstaw element do zdegenerowanego drzewa BST (z koncowki tablicy poczatkowej) - wcisnij 9" << endl;
    cout << "Usun element z drzewa BST - wcisnij 10" << endl;
    cout << "Usun element z zdegenerowanego drzewa BST - wcisnij 12" << endl;
    cout << "Wyswietl drzewo BST - wcisnij 13" << endl;
    cout << "Wyswietl drzewo AVL - wcisnij 14" << endl;
    cout << "Wyswietl zdegenerowane drzewo BST - wcisnij 15" << endl;
    cout << "Usun drzewa i zakoncz dzialanie programu - wcisnij 16" << endl;

}

int opcja(){

    int wybor;

    while(1){

        cout << endl <<  "Wybierz opcje: ";

        if(cin >> wybor){
            cin.ignore();
            break;
        }
    }

    return wybor;
}

int main()
{
        int *tab, *tab_s, rozmiar, menu, elementy;
		int wartosc, r = 100000;

		srand(time(NULL));

		cout << "\nPodaj rozmiar tablicy: ";
		cin >> rozmiar;
		//tab = new int[rozmiar];
		tab_s = new int [rozmiar];
		//t_tab(tab, rozmiar, r);
		t_tabs(tab_s, rozmiar);
		//insertion_sort(tab_s, rozmiar);
		cout << endl;
		//wyswietl_tab(tab, rozmiar);
		cout << endl;
		wyswietl_tab(tab_s, rozmiar);
		cout << endl;

    wyswietl_m();

    while(1){

        menu = opcja();

        switch(menu){

            case 1:
                {

                for(int i = 0; i < rozmiar; i++)
                    bst_drzewo(korzen, tab);
                }
                break;

            case 3:
                {
				for (int i = 0; i < rozmiar; i++)
					bst_drzewol(korzenol, tab_s);
                }
                break;

            case 4:
                {
                cout << "\nPodaj ile elementow chcesz wyszukac: ";
                cin >> elementy;
                for (int i = 0; i < elementy; i++){
                    wartosc = tab[rand() % rozmiar];
                    cout << wyszukaj(korzen, wartosc)->wartosc << " ";
                }
                cout << endl;
                }
                break;

            case 6:
                {
                cout << "\nPodaj ile elementow chcesz wyszukac: ";
                cin >> elementy;
                for(int i = 0; i < elementy; i++){
                    wartosc = tab_s[rand() % rozmiar];
                    cout << wyszukaj(korzenol, wartosc)->wartosc << " ";
                }
                cout << endl;
                }
                break;

            case 7:
                {
                cout << "\nPodaj ile elementow chcesz wstawic: ";
                cin >> elementy;
                for(int i = 0; i < elementy; i++){
                    wartosc = tab[rozmiar - 1 - i];
                    bst_dodawanie(korzen, wartosc);
                }
                cout << endl;
                }
                break;

            case 9:
                {
                cout << "\nPodaj ile elementow chcesz wstawic: ";
                cin >> elementy;
                for(int i = 0; i < elementy; i++){
                    wartosc = tab_s[rozmiar - 1 - i];
                    bst_drzewol(korzenol, wartosc);
                }
                cout << endl;
                }
                break;


            case 10:
                {
                cout << "\nPodaj ile elementow chcesz usunac: ";
                cin >> elementy;
                for(int i = 0; i < elementy; i++){
                    wartosc = tab[rand() % rozmiar];
                    bst_usun(wyszukaj(korzen, wartosc));
                }
                cout << endl;
                }
                break;

            case 12:
                {
                cout << "\nPodaj ile elementow chcesz usunac: ";
                cin >> elementy;
                for(int i = 0; i < elementy; i++){
                    wartosc = tab_s[rand() % rozmiar];
                    bst_usun(wyszukaj(korzenol, wartosc));
                }
                }
                break;

            case 13:
                {
                cout << endl;
                wyswietl_drzewo(korzen);
                cout << endl;
                }
                break;

            case 15:
                {
                cout << endl;
                wyswietl_drzewo(korzenol);
                cout << endl;
                }
                break;

            case 16:
                {
                bst_wycinka(korzen);
                bst_wycinkal(korzenol);
                delete tab;
                delete tab_s;
                exit(0);
                }
                break;
        }
    }

    delete tab;
    delete tab_s;

    return 0;
}
