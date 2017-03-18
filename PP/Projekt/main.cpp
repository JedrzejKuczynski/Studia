#include <ctime>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

struct film{
    int id;
    string tytul;
    struct data{
        int dzien, miesiac, rok;};
    string imie;
    string nazwisko;
    string studio;
    string gat;
    string opis;
    film *next;
    film *prev;

    data dataf;


};

film *head = NULL; // wskaznik na pierwszy element listy
film *poprz = NULL; // wskaznik na ostatni element listy

int counter_id = 0; //globalna zmienna odpowiedzialna za przypisywanie ID

//prototypy funkcji

void wyswietl_m();
void wyswietl(string);
void wyswietl_fid(int);
void wyswietl_wf();
void dodaj(string, int, int, int, string, string, string, string, string);
void usun_tytul(string);
void usun_id(int);
void modyfikacja_id(int);
void modyfikacja(string);
void zapis_plik();
void odczyt_plik(film **head);
int opcja();


int main(){

    int menu, dd, mm, rr, wybor, id;
    string tytul, imie, nazwisko, studio, gat, opis;

    wyswietl_m(); // funkcja wyswietlajaca menu

    while(1){

        menu = opcja();

        switch (menu){

            case 1: //Pobieranie informacji do funkcji dodajacej nowy element listy

                cout <<"\nPodaj tytul filmu:" << endl;
                getline(cin, tytul);
                cout << "\nPodaj date powstania filmu (dd/mm/yyyy), po kazdej wprowadzonej liczbie wcisnij enter" << endl;
                while(!(cin >> dd)){
                    cout << "Wpisales litere!" << endl;
                    cin.clear();
                    cin.sync();
                }
                while(!(cin >> mm)){
                    cout << "Wpisales litere!" << endl;
                    cin.clear();
                    cin.sync();
                }
                while(!(cin >> rr)){
                    cout << "Wpisales litere!" << endl;
                    cin.clear();
                    cin.sync();
                }
                cout << "\nPodaj imie i nazwisko rezysera (wcisnij enter po wprowadzeniu imienia, a nastepnie po wprowadzeniu nazwiska)" << endl;
                cin >> imie >> nazwisko;
                cin.ignore();
                cout << "\nPodaj studio, ktore wyprodukowalo ten film" << endl;
                getline(cin, studio);
                cout <<"\nPodaj gatunek filmu:" << endl;
                getline(cin, gat);
                cout << "\nOpisz film:" << endl;
                getline(cin, opis);
                dodaj (tytul, dd, mm, rr, imie, nazwisko, studio, gat, opis); // wywolanie funkcji dodajacej element
                wyswietl_m();
                break;

            case 2: // usuwanie elementow

                cout << "\nCzy chcesz usunac film po ID czy po tytule? (ID - wcisnij 1, Tytul - wcisnij 2)" << endl;
                cin >> wybor;
                cin.ignore();

                if(wybor == 1){
                    cout << "\nPodaj ID filmu, ktory chcesz usunac:" << endl;
                    cin >> id;
                    usun_id(id); // wywolanie funkcji usuwajacej po ID
                }else if(wybor == 2){
                    cout << "\nPodaj tytul filmu, ktory chcesz usunac:" << endl;
                    getline(cin, tytul);
                    usun_tytul(tytul); //wywolanie funkcji usuwajacej po tytule
                }else
                    cout << "\nWpisales zla cyfre!" << endl;
                wyswietl_m();
                break;

            case 3: //wyszukiwanie elementow

                cout << "\nChcesz wyszukac film po ID czy tytule? (ID - wcisnij 1, Tytul - wcisnij 2)" << endl;
                cin >> wybor;
                cin.ignore();

                if(wybor == 1){
                    cout << "\nPodaj ID filmu, ktory chcesz wyszukac" << endl;
                    cin >> id;
                    wyswietl_fid(id); // funkcja wyszukujaca po ID
                }else if(wybor == 2){
                    cout << "\nPodaj tytul filmu, ktory chcesz wyszukac" << endl;
                    getline(cin, tytul);
                    wyswietl(tytul); // funkcja wyszukujaca po tytule
                }else
                    cout << "\nPodales zla cyfre!" << endl;
                wyswietl_m();
                break;

            case 4: // wyswietlanie filmow

                wyswietl_wf(); // funkcja wyswietlajaca wszystkie filmy
                cout << endl << endl;
                wyswietl_m();
                break;

            case 5: // modyfikacja

                cout << "\nChcesz modyfikowac film po ID czy tytule? (ID - wcisnij 1, Tytul - wcisnij 2)" << endl;
                cin >> wybor;
                cin.ignore();

                if(wybor == 1){
                    cout << "\nPodaj ID filmu, ktorego elementy chcesz modyfikowac" << endl;
                    cin >> id;
                    cin.ignore();
                    modyfikacja_id(id); // funkcja modyfikujaca po ID
                }else if(wybor == 2){
                    cout << "\nPodaj tytul filmu, ktorego elementy chcesz modyfikowac" << endl;
                    getline(cin, tytul);
                    modyfikacja(tytul); // funkcja modyfikujaca po tytule
                }else
                    cout << "\nPodales zla cyfre!" << endl;
                wyswietl_m();
                break;

            case 6: // zapis do pliku

                zapis_plik(); // funkcja zapisujaca do pliku
                wyswietl_m();
                break;

            case 7: // odczyt z pliku (srednio dziala)

                odczyt_plik(&head); // funkcja odczytujaca z pliku
                wyswietl_m();
                break;

            case 8: // koniec programu

                exit(0);

            default:

                cout << "\nPodales zla opcje!" << endl << endl;

        }
    }

    return 0;

}

void wyswietl_m(){ // funkcja wyswietlajaca menu

    cout << "\nDodaj nowy film - wcisnij 1" << endl;
    cout << "Usun film - wcisnij 2" << endl;
    cout << "Wyszukaj film - wcisnij 3" << endl;
    cout << "Wyswietl wszystkie filmy - wcisnij 4" << endl;
    cout << "Edytuj dane filmu - wcisnij 5" << endl;
    cout << "Zapisz do pliku - wcisnij 6" << endl;
    cout << "Odczytaj z pliku - wcisnij 7" << endl;
    cout << "Zakoncz dzialanie programu - wcisnij 8" << endl << endl;
}

int opcja(){ // funkcja pobierajaca opcje do menu

    int menu;

    while(1){

        cout << "Wybierz opcje: " << endl;

        if(cin >> menu){
            cin.ignore();
            break;
        }
    }

    return menu;
}

void dodaj (string tyt, int d, int m, int r, string im, string nazw, string studio, string gat, string opis){ // funkcja dodajaca nowy film

    if(head == NULL) { // jezeli lista jest pusta to tworzy nowy obiekt i przypisuje wartosci
            head = new film;
            counter_id++;

            head->next = NULL;
            head->prev = NULL;

            head->id = counter_id;
            head->tytul = tyt;
            head->dataf.dzien = d;
            head->dataf.miesiac = m;
            head->dataf.rok = r;
            head->imie = im;
            head->nazwisko = nazw;
            head->studio = studio;
            head->gat = gat;
            head->opis = opis;

            poprz = head;
            }else { // jezeli lista nie jest pusta to dodaje kolejny element na koniec listy
                film *f = new film;
                counter_id++;

                poprz->next = f;
                f->prev = poprz;
                f->next = NULL;

                f->id = counter_id;
                f->tytul = tyt;
                f->dataf.dzien = d;
                f->dataf.miesiac = m;
                f->dataf.rok = r;
                f->imie = im;
                f->nazwisko = nazw;
                f->studio = studio;
                f->gat = gat;
                f->opis = opis;

                poprz = f;
                }

}

void usun_tytul(string tyt){ // funkcja usuwajaca po tytule

    film *tmp = head; // pomocniczy wskaznik wskazujacy na poczatek listy

    while(tmp != NULL && tmp->tytul != tyt) // wyszukiwanie naszego filmu
        tmp = tmp->next;

    if (tmp == head){ // jezeli usuwanym elementem jest pierwszy, to nastepuje odpowiednia modyfikacja wskaznikow
        head = head->next;
        tmp->next->prev = NULL;
    }else if (tmp != NULL && tmp->next != NULL){ // jezeli usuwanym elementem jest element w srodku listy, to nastepuje odpowiednia modyfikacja wskaznikow
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }else if (tmp != NULL && tmp->next == NULL){ // jezeli usuwanym elementem jest ostatni element, to nastepuje odpowiednia modyfikacja wskaznikow
        poprz = poprz->prev;
        tmp->prev->next = NULL;
    }else{
        cout << "\nFilm o tym tytule nie wystepuje w bazie." << endl; // powiadomienie o bledzie
    }

    delete(tmp); // usuniecie z pamieci naszego pomocniczego wskaznika
}

void usun_id(int id){ // to samo co u gory tylko po ID

    film *tmp = head;

    while(tmp != NULL && tmp->id != id)
        tmp = tmp->next;

    if (tmp == head){
        head = head->next;
        tmp->next->prev = NULL;
    }else if (tmp != NULL && tmp->next != NULL){
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }else if (tmp != NULL && tmp->next == NULL){
        poprz = poprz->prev;
        tmp->prev->next = NULL;
    }else{
        cout << "\nFilm o tym ID nie wystepuje w bazie." << endl;
    }

    delete(tmp);
}

void wyswietl(string tyt){ // wyswietlanie wszystkich danych filmu po tytule

    film *tmp = head; // pomocniczy wskaznik na poczatek listy
    cout << endl;

    while(tmp != NULL && tmp->tytul != tyt) // szukanie naszego filmu
        tmp = tmp->next;

    if(tmp != NULL){ // wyswietlanie danych

    cout << "ID: " << tmp->id << endl << "Tytul: " << tmp->tytul << endl << "Data produkcji: " << tmp->dataf.dzien << "/"
     << tmp->dataf.miesiac << "/" << tmp->dataf.rok << endl << "Imie i nazwisko rezysera: " << tmp->imie << " " << tmp->nazwisko
     << endl << "Studio: " << tmp->studio << endl << "Gatunek: " << tmp->gat << endl << "Opis filmu:\n\n" << tmp->opis << endl << endl;
    }else
        cout << "\nFilmu o podanym tytule nie ma w bazie." << endl; // Powiadomienie o bledzie
    delete(tmp); // usuniecie naszego pomocniczego wskaznika z pamieci
}

void wyswietl_fid(int id){ // to samo tylko po ID

    film *tmp = head;
    cout << endl;

    while(tmp != NULL && tmp->id != id)
        tmp = tmp->next;

    if(tmp != NULL){

    cout << "ID: " << tmp->id << endl << "Tytul: " << tmp->tytul << endl << "Data produkcji: " << tmp->dataf.dzien << "/"
     << tmp->dataf.miesiac << "/" << tmp->dataf.rok << endl << "Imie i nazwisko rezysera: " << tmp->imie << " " << tmp->nazwisko
     << endl << "Studio: " << tmp->studio << endl << "Gatunek: " << tmp->gat << endl << "Opis filmu:\n\n" << tmp->opis << endl << endl;
    }else
        cout << "\nFilmu o podanym ID nie ma w bazie." << endl;
}

void wyswietl_wf(){ // to samo co dwie funkcje u gory, lecz wyswietlanie tytulu i daty produkcji wszystkich filmow

    film *tmp = head;
    cout << endl;

    if(tmp == NULL){
		cout << "\nBrak elementow" << endl;
    }else{
        while(tmp != NULL){

           cout << tmp->tytul << "\t" << tmp->dataf.dzien << "/" << tmp->dataf.miesiac << "/" << tmp->dataf.rok << endl;
            tmp = tmp->next;
        }

    }

    delete (tmp);
}

void modyfikacja_id(int id){ // modyfikacja po ID

    film *tmp = head; // wkaznik pomocniczy na poczatek listy
    string zmiana;
    int new_data;
    cout << endl;

    while(tmp != NULL && tmp->id != id) // szukanie naszego filmu
        tmp = tmp->next;

    if(tmp != NULL){ // modyfikacja wartosci


    cout << "\nPodaj nowy tytul filmu (wcisnij enter, jezeli ma zostac stary)" << endl;
    getline(cin, zmiana); // getline pozwala na pobranie znaku pustego
    if(!zmiana.empty()) // Jezeli jednak cos wprowadzilismy to nastepuje zamiana wartosci
        tmp->tytul = zmiana;

    cout << "\nPodaj nowy dzien, w ktorym film zostal wyprodukowany (wcisnij enter, jezeli ma zostac stary)" << endl;

    while(1){
    getline(cin, zmiana);
    if(!zmiana.empty()){
        new_data = atoi(zmiana.c_str()); // getline pobiera zmienne typu string, wiec konwersja na inta jest niezbedna
        tmp->dataf.dzien = new_data;
        break;
        }else
            break;
    }

    cout << "\nPodaj nowy miesiac, w ktorym film zostal wyprodukowany (wcisnij enter, jezeli ma zostac stary)" << endl;

    while(1){
    getline(cin, zmiana);
    if(!zmiana.empty()){
        new_data = atoi(zmiana.c_str());
        tmp->dataf.miesiac = new_data;
        break;
        }else
            break;
    }

    cout << "\nPodaj nowy rok, w ktorym film zostal wyprodukowany (wcisnij enter, jezeli ma zostac stary)" << endl;

    while(1){
    getline(cin, zmiana);
    if(!zmiana.empty()){
        new_data = atoi(zmiana.c_str());
        tmp->dataf.rok = new_data;
        break;
        }else
            break;
    }

    cout << "\nPodaj nowe imie rezysera filmu (wcisnij enter, jezeli ma zostac stare)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->imie = zmiana;

    cout << "\nPodaj nowe nazwisko rezysera filmu (wcisnij enter, jezeli ma zostac stare)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->nazwisko = zmiana;

    cout << "\nPodaj nowe studio odpowiedzialne za wyprodukowanie filmu (wcisnij enter, jezeli ma zostac stare)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->studio = zmiana;

    cout << "\nPodaj nowy gatunek filmu (wcisnij enter jezeli ma zostac stary)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->gat = zmiana;

    cout << "\nPodaj nowy opis filmu (wcisnij enter jezeli ma zostac stary)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->opis = zmiana;

}else
    cout << "Filmu o podanym ID nie ma w bazie." << endl;

}

void modyfikacja(string tyt){ // to samo tylko ze po tytule

    film *tmp = head;
    string zmiana;
    int new_data;
    cout << endl;

    while(tmp != NULL && tmp->tytul != tyt)
        tmp = tmp->next;

    if(tmp != NULL){


    cout << "\nPodaj nowy tytul filmu (wcisnij enter, jezeli ma zostac stary)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->tytul = zmiana;

    cout << "\nPodaj nowy dzien, w ktorym film zostal wyprodukowany (wcisnij enter, jezeli ma zostac stary)" << endl;

    while(1){
    getline(cin, zmiana);
    if(!zmiana.empty()){
        new_data = atoi(zmiana.c_str());
        tmp->dataf.dzien = new_data;
        break;
        }else
            break;
    }

    cout << "\nPodaj nowy miesiac, w ktorym film zostal wyprodukowany (wcisnij enter, jezeli ma zostac stary)" << endl;

    while(1){
    getline(cin, zmiana);
    if(!zmiana.empty()){
        new_data = atoi(zmiana.c_str());
        tmp->dataf.miesiac = new_data;
        break;
        }else
            break;
    }

    cout << "\nPodaj nowy rok, w ktorym film zostal wyprodukowany (wcisnij enter, jezeli ma zostac stary)" << endl;

    while(1){
    getline(cin, zmiana);
    if(!zmiana.empty()){
        new_data = atoi(zmiana.c_str());
        tmp->dataf.rok = new_data;
        break;
        }else
            break;
    }

    cout << "\nPodaj nowe imie rezysera filmu (wcisnij enter, jezeli ma zostac stare)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->imie = zmiana;

    cout << "\nPodaj nowe nazwisko rezysera filmu (wcisnij enter, jezeli ma zostac stare)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->nazwisko = zmiana;

    cout << "\nPodaj nowe studio odpowiedzialne za wyprodukowanie filmu (wcisnij enter, jezeli ma zostac stare)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->studio = zmiana;

    cout << "\nPodaj nowy gatunek filmu (wcisnij enter jezeli ma zostac stary)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->gat = zmiana;

    cout << "\nPodaj nowy opis filmu (wcisnij enter jezeli ma zostac stary)" << endl;
    getline(cin, zmiana);
    if(!zmiana.empty())
        tmp->opis = zmiana;

}else
    cout << "Filmu o podanym tytule nie ma w bazie." << endl;

}

void zapis_plik(){ // funkcja zapisujaca do pliku


    film *tmp = head; // pomocniczy wskaznik na poczatek listy
    string p_nazwa;

    cout << "\nPodaj nazwe pliku:" << endl;
    cin >> p_nazwa; // pobieranie nazwy pliku
    p_nazwa += ".txt"; // i dolaczanie do niego rozszerzenia .txt
    ofstream plik; // obsluga wyjscia plikowego dla pliku "plik"

    plik.open(p_nazwa.c_str()); // otworzenie pliku "plik"

    while(tmp != NULL){ // zapisywanie wartosci kazdego elementu listy

        plik << tmp->id << "\n";
        plik << tmp->tytul << "\n";
        plik << tmp->dataf.dzien << "\n" << tmp->dataf.miesiac << "\n" << tmp->dataf.rok << "\n";
        plik << tmp->imie << "\n";
        plik << tmp->nazwisko << "\n";
        plik << tmp->studio << "\n";
        plik << tmp->gat << "\n";
        plik << tmp->opis << "\n";

        tmp = tmp->next;
    }

    plik.close(); // zamkniecie pliku
    cout << "\nLista zostala zapisana!" << endl << endl;
    delete (tmp); // usuniecie pomocniczego wskaznika

}

void odczyt_plik(film **head){ // funkcja odczytujaca z pliku (srednio dziala)

    ifstream plik;
    string p_nazwa, linia;
    film *tmp, *tmp1;


    cout << "Podaj nazwe pliku: " << endl;
    cin >> p_nazwa;


    plik.open(p_nazwa.c_str());

    if(plik == NULL){
        cout << "Nie udalo sie otworzyc pliku." << endl;
        plik.close();
    }else{

        while(getline(plik, linia)){

                int i = 0, data;
                string div;
                tmp = new film;
                tmp->next = NULL;
                tmp->prev = NULL;

                istringstream iss(linia);

                while(getline(iss, div, '\n')){


                    switch(i){

                        case 0:

                            data = atoi(div.c_str());
                            tmp->id = data;
                            counter_id++;
                            break;

                        case 1:

                            tmp->tytul = div;
                            break;

                        case 2:

                            data = atoi(div.c_str());
                            tmp->dataf.dzien = data;
                            break;

                        case 3:

                            data = atoi(div.c_str());
                            tmp->dataf.miesiac = data;
                            break;

                        case 4:

                            data = atoi(div.c_str());
                            tmp->dataf.rok = data;
                            break;

                        case 5:

                            tmp->imie = div;
                            break;

                        case 6:

                            tmp->nazwisko = div;
                            break;

                        case 7:

                            tmp->studio = div;
                            break;

                        case 8:

                            tmp->gat = div;
                            break;

                        case 9:

                            tmp->opis = div;
                            break;

                        default:

                            cout << "Wystapil blad." << endl;

                    }
                    i++;
                }



        if(*head == NULL)
            *head = tmp;
        else{

            tmp1 = *head;
            while(tmp1->next != NULL)
                tmp1 = tmp1->next;
            tmp->prev = tmp1;
            tmp1->next = tmp;
        }



        }

    plik.close();
    }

    }








