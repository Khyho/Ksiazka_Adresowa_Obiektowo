#include <iostream>
#include <cstdlib>
#include "KsiazkaAdresatow.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

KsiazkaAdresatow::KsiazkaAdresatow (int i=0,int iU=0, string im="", string naz="", string nrTel="", string em="", string adr=""):Adresat(i,iU, im, naz, nrTel, em, adr){}

void KsiazkaAdresatow::wczytajOsobyZPlikuDlaDanegoUzytkownika (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika){
    KsiazkaAdresatow osobaZKsiazkiAdresowej (0,0,"","","","","");
    int nrLinii=1;
    int licznik = 0;
    string linia;
    string rekordPomocniczy="";
    string wyrazPomocniczy="";
    fstream plik;

    ksiazkaAdresowa.clear();

    plik.open("Ksiazka_Adresowa.txt", ios::in);

    while (getline(plik,linia)){
        switch(nrLinii){
        case 1:
            rekordPomocniczy = linia;
            for (int i = 0; i<rekordPomocniczy.length();i++){
                if (rekordPomocniczy[i]!=124){
                    wyrazPomocniczy+=rekordPomocniczy[i];
                } else if (rekordPomocniczy[i]==124){
                    licznik++;
                    switch(licznik){
                        case 1:
                            osobaZKsiazkiAdresowej.id = atoi(wyrazPomocniczy.c_str());
                            wyrazPomocniczy ="";
                            break;
                        case 2:
                            osobaZKsiazkiAdresowej.idUzytkownika = atoi(wyrazPomocniczy.c_str());
                            wyrazPomocniczy ="";
                            break;
                        case 3:
                            osobaZKsiazkiAdresowej.imie = wyrazPomocniczy;
                            wyrazPomocniczy ="";
                            break;
                        case 4:
                            osobaZKsiazkiAdresowej.nazwisko = wyrazPomocniczy;
                            wyrazPomocniczy ="";
                            break;
                        case 5:
                            osobaZKsiazkiAdresowej.email = wyrazPomocniczy;
                            wyrazPomocniczy = "";
                            break;
                        case 6:
                            osobaZKsiazkiAdresowej.numerTelefonu = wyrazPomocniczy;
                            wyrazPomocniczy = "";
                            break;
                        case 7:
                            osobaZKsiazkiAdresowej.adres = wyrazPomocniczy;
                            wyrazPomocniczy = "";
                            break;
                    }
                }
            }
            break;

        }
        if (nrLinii==1 && osobaZKsiazkiAdresowej.idUzytkownika==idUzytkownika){
            ksiazkaAdresowa.push_back(osobaZKsiazkiAdresowej);
            licznik = 0;
            nrLinii=0;
        }
        else {
            licznik = 0;
            nrLinii=0;
        }
        nrLinii++;
    }
    plik.close();
}

void KsiazkaAdresatow::wprowadzanieNowychOsobDoKsiazki (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika){
    KsiazkaAdresatow osobaZKsiazkiAdresowej(0,0,"","","","","");
    int i=0;
    system ("cls");

    osobaZKsiazkiAdresowej.id = okreslID(ksiazkaAdresowa, idUzytkownika);

    osobaZKsiazkiAdresowej.idUzytkownika = idUzytkownika;

    cout << "Podaj Imie: "<<endl;
    cin>> osobaZKsiazkiAdresowej.imie;
    osobaZKsiazkiAdresowej.imie = zamienWielkoscLiter(osobaZKsiazkiAdresowej.imie);
    cout <<"Podaj nazwisko: "<<endl;
    cin >> osobaZKsiazkiAdresowej.nazwisko;
    osobaZKsiazkiAdresowej.nazwisko = zamienWielkoscLiter(osobaZKsiazkiAdresowej.nazwisko);
    while (i <ksiazkaAdresowa.size()){
        if (ksiazkaAdresowa[i].imie == osobaZKsiazkiAdresowej.imie && ksiazkaAdresowa[i].nazwisko==osobaZKsiazkiAdresowej.nazwisko ){
            system ("cls");
            cout << "Taki uzytkownik juz istnieje. Wprowadz ponownie."<<endl;
            cout << "Podaj imie:"<<endl;
            cin>> osobaZKsiazkiAdresowej.imie;
            osobaZKsiazkiAdresowej.imie = zamienWielkoscLiter(osobaZKsiazkiAdresowej.imie);
            cout <<"Podaj nazwisko:"<<endl;
            cin >> osobaZKsiazkiAdresowej.nazwisko;
            osobaZKsiazkiAdresowej.nazwisko = zamienWielkoscLiter(osobaZKsiazkiAdresowej.nazwisko);
            i=0;
        }else{
            i++;
        }
    }
    cout <<"Podaj email: "<<endl;
    cin >> osobaZKsiazkiAdresowej.email;
    cout <<"Podaj numer telefonu: "<<endl;
    cin.sync();
    getline(cin,osobaZKsiazkiAdresowej.numerTelefonu);
    cout <<"Podaj adres: "<<endl;
    cin.sync();
    getline(cin,osobaZKsiazkiAdresowej.adres);

    ksiazkaAdresowa.push_back(osobaZKsiazkiAdresowej);

    zapiszOsobyDoPliku(osobaZKsiazkiAdresowej, ksiazkaAdresowa);

    cout << "Osoba zapisana w ksiazce adresowej pod numerem "<<osobaZKsiazkiAdresowej.id<<endl;
    Sleep(3000);
}

string KsiazkaAdresatow::zamienWielkoscLiter (string tekstDoZamiany){
    transform(tekstDoZamiany.begin(),tekstDoZamiany.begin()+1,tekstDoZamiany.begin(),::toupper);
    transform(tekstDoZamiany.begin()+1,tekstDoZamiany.end(),tekstDoZamiany.begin()+1,::tolower);
return tekstDoZamiany;
}

int KsiazkaAdresatow::okreslID (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika){
    int id = 0;
    ksiazkaAdresowa.clear();
    wczytajWszystkieOsobyZPliku(ksiazkaAdresowa);

    if (ksiazkaAdresowa.empty()==true){
        id = 1;
    }
    else{
        id = ksiazkaAdresowa.back().id + 1;
    }

    ksiazkaAdresowa.clear();
    wczytajOsobyZPlikuDlaDanegoUzytkownika (ksiazkaAdresowa, idUzytkownika);

    return id;
}

void KsiazkaAdresatow::wczytajWszystkieOsobyZPliku (vector <Adresat> &ksiazkaAdresowa){
    KsiazkaAdresatow osobaZKsiazkiAdresowej(0,0,"","","","","");
    int nrLinii=1;
    int x=0;
    int licznik = 0;
    string linia;
    string rekordPomocniczy="";
    string wyrazPomocniczy="";
    fstream plik;

    ksiazkaAdresowa.clear();

    plik.open("Ksiazka_Adresowa.txt", ios::in);

    while (getline(plik,linia)){
        switch(nrLinii){
        case 1:
            rekordPomocniczy = linia;
            for (int i = 0; i<rekordPomocniczy.length();i++){
                if (rekordPomocniczy[i]!=124){
                    wyrazPomocniczy+=rekordPomocniczy[i];
                } else if (rekordPomocniczy[i]==124){
                    licznik++;
                    switch(licznik){
                        case 1:
                            osobaZKsiazkiAdresowej.id = atoi(wyrazPomocniczy.c_str());
                            wyrazPomocniczy ="";
                            break;
                        case 2:
                            osobaZKsiazkiAdresowej.idUzytkownika = atoi(wyrazPomocniczy.c_str());
                            wyrazPomocniczy ="";
                            break;
                        case 3:
                            osobaZKsiazkiAdresowej.imie = wyrazPomocniczy;
                            wyrazPomocniczy ="";
                            break;
                        case 4:
                            osobaZKsiazkiAdresowej.nazwisko = wyrazPomocniczy;
                            wyrazPomocniczy ="";
                            break;
                        case 5:
                            osobaZKsiazkiAdresowej.email = wyrazPomocniczy;
                            wyrazPomocniczy = "";
                            break;
                        case 6:
                            osobaZKsiazkiAdresowej.numerTelefonu = wyrazPomocniczy;
                            wyrazPomocniczy = "";
                            break;
                        case 7:
                            osobaZKsiazkiAdresowej.adres = wyrazPomocniczy;
                            wyrazPomocniczy = "";
                            break;
                    }
                }
            }
            break;

        }
        if (nrLinii==1){
            ksiazkaAdresowa.push_back(osobaZKsiazkiAdresowej);
            licznik = 0;
            nrLinii=0;
        }
        nrLinii++;
    }
    plik.close();
}

void KsiazkaAdresatow::zapiszOsobyDoPliku (Adresat osobaZKsiazkiAdresowej, vector <Adresat> &ksiazkaAdresowa){
    fstream plik;
    plik.open("Ksiazka_Adresowa.txt", ios::out | ios::app);
    if (plik.good()==false && ksiazkaAdresowa.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    plik<<osobaZKsiazkiAdresowej.id<<"|"<<osobaZKsiazkiAdresowej.idUzytkownika<<"|"<<osobaZKsiazkiAdresowej.imie<<"|"<<osobaZKsiazkiAdresowej.nazwisko<<"|"<<osobaZKsiazkiAdresowej.email<<"|"<<osobaZKsiazkiAdresowej.numerTelefonu<<"|"<<osobaZKsiazkiAdresowej.adres<<"|"<<endl;
    plik.close();
}

void KsiazkaAdresatow::wyszukiwaniePoImieniu (vector <Adresat> &ksiazkaAdresowa){
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!ksiazkaAdresowa.empty())
    {   cout << "Wyszukaj osoby o imieniu: ";
        cin >> imiePoszukiwanegoAdresata;
        imiePoszukiwanegoAdresata = zamienWielkoscLiter(imiePoszukiwanegoAdresata);

        for (vector <Adresat>::iterator  itr = ksiazkaAdresowa.begin(); itr != ksiazkaAdresowa.end(); itr++)
        {
            if (itr -> imie == imiePoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr -> id << endl;
                cout << "Imie:               " << itr -> imie << endl;
                cout << "Nazwisko:           " << itr -> nazwisko << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imiePoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void KsiazkaAdresatow::wyszukiwaniePoNazwisku(vector <Adresat> &ksiazkaAdresowa){
    string nazwiskoPoszukiwanegoAdresata;
    int iloscAdresatow = 0;

    system("cls");
    if (!ksiazkaAdresowa.empty())
    {   cout << "Wyszukaj adresatow o nazwisku: ";
        cin >> nazwiskoPoszukiwanegoAdresata;
        nazwiskoPoszukiwanegoAdresata = zamienWielkoscLiter(nazwiskoPoszukiwanegoAdresata);

        for (vector <Adresat>::iterator itr = ksiazkaAdresowa.begin(); itr != ksiazkaAdresowa.end(); itr++)
        {
            if (itr -> nazwisko == nazwiskoPoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr -> id << endl;
                cout << "Imie:               " << itr -> imie << endl;
                cout << "Nazwisko:           " << itr -> nazwisko << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwiskoPoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void KsiazkaAdresatow::pokazWszystkich (vector <Adresat> &ksiazkaAdresowa){
    system("cls");
    if (!ksiazkaAdresowa.empty())
    {
        for (vector <Adresat> :: iterator itr = ksiazkaAdresowa.begin(); itr != ksiazkaAdresowa.end(); itr++)
        {
            cout << "Id:                 " << itr -> id << endl;
            cout << "Imie:               " << itr -> imie << endl;
            cout << "Nazwisko:           " << itr -> nazwisko << endl;
            cout << "Numer telefonu:     " << itr -> numerTelefonu << endl;
            cout << "Email:              " << itr -> email << endl;
            cout << "Adres:              " << itr -> adres << endl << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void KsiazkaAdresatow::usun (vector <Adresat> &ksiazkaAdresowa, int idUsuwanejOsoby, int idUzytkownika){

    wczytajWszystkieOsobyZPliku (ksiazkaAdresowa);
    for (vector <Adresat>::iterator itr = ksiazkaAdresowa.begin(); itr != ksiazkaAdresowa.end(); itr++){
        if (itr -> id == idUsuwanejOsoby){
            ksiazkaAdresowa.erase(itr);
            cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
            zapiszOsobyDoPlikuNadpisujacPlik(ksiazkaAdresowa, idUzytkownika);
            break;
        }
    }
}

void KsiazkaAdresatow::usuwanieRekorduZPliku (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika){
    int idUsuwanejOsoby = 0;
    char znak;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!ksiazkaAdresowa.empty()){
        cout << "Podaj numer ID osoby do usuniecia: ";
        cin >> idUsuwanejOsoby;

        if (cin.fail()){
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl;
            cin.clear();
            cin.sync();
        } else {
            for (vector <Adresat>::iterator itr = ksiazkaAdresowa.begin(); itr != ksiazkaAdresowa.end(); itr++){
                if (itr -> id == idUsuwanejOsoby){
                    czyIstniejeAdresat = true;
                    cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                    cin >> znak;
                    if (znak == 't'){
                        usun (ksiazkaAdresowa, idUsuwanejOsoby, idUzytkownika);
                        break;
                    } else {
                        cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                        break;
                    }
                }
            }
            if (czyIstniejeAdresat == false)
            {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
            }
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    system("pause");
}

void KsiazkaAdresatow::zapiszOsobyDoPlikuNadpisujacPlik (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika){

    fstream plik;
    int i=0;
    plik.open("Ksiazka_Adresowa.txt", ios::out);
    if (plik.good()==false && ksiazkaAdresowa.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    while (i<ksiazkaAdresowa.size()){
    plik<<ksiazkaAdresowa[i].id<<"|"<<ksiazkaAdresowa[i].idUzytkownika<<"|"<<ksiazkaAdresowa[i].imie<<"|"<<ksiazkaAdresowa[i].nazwisko<<"|"<<ksiazkaAdresowa[i].email<<"|"<<ksiazkaAdresowa[i].numerTelefonu<<"|"<<ksiazkaAdresowa[i].adres<<"|"<<endl;
    i++;
    }
    plik.close();

    ksiazkaAdresowa.clear();

    wczytajOsobyZPlikuDlaDanegoUzytkownika (ksiazkaAdresowa, idUzytkownika);
}

void KsiazkaAdresatow::zaktualizujRekordwKsiazceAdresowej (vector <Adresat> &ksiazkaAdresowa, int idWybranegoAdresata, int wybor){
    wczytajWszystkieOsobyZPliku (ksiazkaAdresowa);
    for (vector <Adresat>::iterator itr = ksiazkaAdresowa.begin(); itr <= ksiazkaAdresowa.end(); itr++){
        if (itr -> id == idWybranegoAdresata){
            switch (wybor){
                case '1':
                    cout << "Podaj nowe imie: ";
                    cin >> itr -> imie;
                    itr -> imie = zamienWielkoscLiter(itr -> imie);
                    cout << endl << "Imie zostalo zmienione" << endl << endl;
                    zapiszOsobyDoPlikuNadpisujacPlik(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    cin >> itr -> nazwisko;
                    itr -> nazwisko = zamienWielkoscLiter(itr -> nazwisko);
                    cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                    zapiszOsobyDoPlikuNadpisujacPlik(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    cin >> itr -> numerTelefonu;
                    cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                    zapiszOsobyDoPlikuNadpisujacPlik(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    cin >> itr -> email;
                    cout << endl << "Email zostal zmieniony" << endl << endl;
                    zapiszOsobyDoPlikuNadpisujacPlik(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '5':
                    cout << "Podaj nowy adres zamieszkania: ";
                    cin >> itr -> adres;
                    itr -> adres = zamienWielkoscLiter(itr -> adres);
                    cout << endl << "Adres zostal zmieniony" << endl << endl;
                    zapiszOsobyDoPlikuNadpisujacPlik(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '9':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
}

void KsiazkaAdresatow::edytujRekord (vector <Adresat> &ksiazkaAdresowa, int idUzytkownika){
    int idWybranegoAdresata = 0;
    char wybor;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!ksiazkaAdresowa.empty())
    {   cout << "Podaj numer ID osoby do edycji: ";
        cin >> idWybranegoAdresata;

        if (cin.fail())
        {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            for (vector <Adresat>::iterator itr = ksiazkaAdresowa.begin(); itr <= ksiazkaAdresowa.end(); itr++)
            {
                if (itr -> id == idWybranegoAdresata)
                {
                    czyIstniejeAdresat = true;

                    cout << "Jaka dane chcesz zmienic?"<<endl;
                    cout << "1. Imie"<<endl;
                    cout << "2. Nazwisko"<<endl;
                    cout << "3. eMail"<<endl;
                    cout << "4. Numer Telefonu"<<endl;
                    cout << "5. Adres"<<endl;
                    cout << "9. Cofnij"<<endl;
                    cin >> wybor;

                    zaktualizujRekordwKsiazceAdresowej(ksiazkaAdresowa, idWybranegoAdresata, wybor);
                    wczytajOsobyZPlikuDlaDanegoUzytkownika(ksiazkaAdresowa, idUzytkownika);
                }
            }
            if (czyIstniejeAdresat == false)
            {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
            }
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}
