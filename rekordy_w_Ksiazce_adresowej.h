#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class Adresat {
int id, idUzytkownika;
string imie, nazwisko, numerTelefonu, email, adres;

string zamienWielkoscLiter (string tekstDoZamiany);
int okreslID (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika);
void wczytajWszystkieOsobyZPliku (vector <Adresat> &ksiazkaAdresowa);
void zapiszOsobyDoPliku (Adresat osoba, vector <Adresat> &ksiazkaAdresowa);
void zapiszOsobyDoPlikuNadpisujacPlik (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika);

public:
Adresat (int , int , string , string, string, string, string);
void wczytajOsobyZPlikuDlaDanegoUzytkownika (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika);
void wprowadzanieNowychOsobDoKsiazki (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika);
void wyszukiwaniePoImieniu (vector <Adresat> &ksiazkaAdresowa);
void wyszukiwaniePoNazwisku(vector <Adresat> &ksiazkaAdresowa);
void pokazWszystkich (vector <Adresat> &ksiazkaAdresowa);
void usuwanieRekorduZPliku (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika);
void edytujRekord (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika);
};

