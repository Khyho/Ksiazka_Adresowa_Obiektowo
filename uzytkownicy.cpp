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

Uzytkownik::Uzytkownik (int i, string log, string pas){
    idUzytkownika = i;
    login = log;
    haslo = pas;
}

bool Uzytkownik::wczytajUzytkownikowProgramu (vector <Uzytkownik> &daneDoLogowania, int idUzytkownika){

    Uzytkownik osoba (0, "", "");
    int nrLinii=idUzytkownika+1;
    int aktualnyNumer=1;
    int licznik = 0;
    string linia;
    string rekordPomocniczy="";
    string wyrazPomocniczy="";
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::in);
    while (getline(plik,linia)){
        if (aktualnyNumer == nrLinii){
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

void Uzytkownik::rejestracja (vector <Uzytkownik> &daneDoLogowania) {
    Uzytkownik uzytkownikProgramu (0, "", "");
    int i=0;
    system ("cls");
    if (daneDoLogowania.empty()==true){
        uzytkownikProgramu.idUzytkownika = 1;
    }
    else{
        uzytkownikProgramu.idUzytkownika = daneDoLogowania.back().idUzytkownika + 1;
    }

    cout << "Podaj Login: "<<endl;
    cin>> uzytkownikProgramu.login;

    cout <<"Podaj haslo: "<<endl;
    cin >> uzytkownikProgramu.haslo;

    while (i <daneDoLogowania.size()){
        if (daneDoLogowania[i].login == uzytkownikProgramu.login && daneDoLogowania[i].haslo==uzytkownikProgramu.haslo ){
            system ("cls");
            cout << "Taki uzytkownik juz istnieje. Wprowadz ponownie."<<endl;
            cout << "Podaj Login: "<<endl;
            cin>> uzytkownikProgramu.login;

            cout <<"Podaj haslo: "<<endl;
            cin >> uzytkownikProgramu.haslo;
            i=0;
        }else{
            i++;
        }
    }

    daneDoLogowania.push_back(uzytkownikProgramu);

    zapiszUzytkownikowWPliku(uzytkownikProgramu, daneDoLogowania);

    cout << "Utworzono nowego uzytkownika o numerze "<<uzytkownikProgramu.idUzytkownika<<endl;
    Sleep(3000);

}

void Uzytkownik::zapiszUzytkownikowWPliku (Uzytkownik uzytkownikProgramu, vector <Uzytkownik> &daneDoLogowania){
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (plik.good()==false && daneDoLogowania.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    plik<<uzytkownikProgramu.idUzytkownika<<"|";
    plik<<uzytkownikProgramu.login<<"|";
    plik<<uzytkownikProgramu.haslo<<"|"<<endl;
    plik.close();
}

int Uzytkownik::logowanie (vector <Uzytkownik> &daneDoLogowania){
    string login = "", haslo = "";

    vector <Uzytkownik>::iterator itr = daneDoLogowania.begin();
    for (int proby = 3; proby > 0; proby--){
            cout << "LOGOWANIE."<<endl;
            cout <<  "Podaj login: "<<endl;
            cin >> login;

            cout << "Podaj haslo: "<<endl;
            cin >> haslo;

            for (;itr != daneDoLogowania.end();itr++){
                if (itr -> login == login && itr -> haslo == haslo){
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    return itr -> idUzytkownika;
                }
            }
                cout << "Blednie podany login i/lub haslo."<<endl;
                cout <<"Pozostalo: "<<proby-1<<" proby."<<endl;
                system("pause");
                itr = daneDoLogowania.begin();
                system("cls");
    }
    cout << "Wprowadzono 3 razy bledne login i/lub haslo. Powrot do menu glownego." << endl;
    system("pause");
    return 0;
}

void Uzytkownik::zmianaHasla (vector <Uzytkownik> &daneDoLogowania, int idUzytkownika){
    string noweHaslo;
    cout << "Wprowadz nowe haslo: ";
    cin >> noweHaslo;
    vector <Uzytkownik>::iterator itr = daneDoLogowania.begin()+idUzytkownika-1;
    itr -> haslo = noweHaslo;
    zapiszUzytkownikowWPlikuNadpisujacPlik(daneDoLogowania);

}

void Uzytkownik::zapiszUzytkownikowWPlikuNadpisujacPlik (vector <Uzytkownik> &daneDoLogowania){
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);
    if (plik.good()==false && daneDoLogowania.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    for (vector <Uzytkownik>::iterator itr = daneDoLogowania.begin(); itr != daneDoLogowania.end(); itr++){
    plik<<itr -> idUzytkownika<<"|";
    plik<<itr -> login<<"|";
    plik<<itr -> haslo<<"|"<<endl;
    }
    plik.close();
}
