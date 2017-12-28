#include <iostream>
#include "uzytkownicy.h"
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

bool Uzytkownik::wczytajUzytkownikowProgramu (vector <Uzytkownik> &daneDoLogowania, int idUzytkownika){

    Uzytkownik osoba;
    int nr_linii=idUzytkownika+1;
    int aktualnyNumer=1;
    int licznik = 0;
    string linia;
    string rekordPomocniczy="";
    string wyrazPomocniczy="";
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::in);
    while (getline(plik,linia)){
        if (aktualnyNumer == nr_linii){
            rekordPomocniczy = linia;
            for (int i = 0; i<rekordPomocniczy.length();i++){
                if (rekordPomocniczy[i]!=124){
                    wyrazPomocniczy+=rekordPomocniczy[i];
                } else if (rekordPomocniczy[i]==124){
                    licznik++;
                    switch(licznik){
                        case 1:
                            osoba.idUzytkownika = atoi(wyrazPomocniczy.c_str());
                            wyrazPomocniczy ="";
                            break;
                        case 2:
                            osoba.login = wyrazPomocniczy;
                            wyrazPomocniczy ="";
                            break;
                        case 3:
                            osoba.haslo = wyrazPomocniczy;
                            wyrazPomocniczy ="";
                            break;
                    }
                }
            }
        daneDoLogowania.push_back(osoba);
        return true;
        }
        aktualnyNumer++;
    }
    return false;
    plik.close();
}





