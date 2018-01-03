#include <iostream>
#include "uzytkownicy.h"
#include "rekordy_w_Ksiazce_adresowej.h"
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;


int main(){
    vector <Adresat> ksiazkaAdresowa;
    vector <Uzytkownik> daneDoLogowania;

    Adresat osobaZKsiazkiAdresowej(0,0,"","","","","");
    Uzytkownik osoba (0, "", "");

    char wybor='0';
    int idUzytkownika=0;
    int licznikUzytkownikow=0;

    while (osoba.wczytajUzytkownikowProgramu(daneDoLogowania, licznikUzytkownikow)==true){
    licznikUzytkownikow++;
    }


    while (true){
        if (idUzytkownika==0){
            system ("cls");
            cout << "Witaj w ksiazce adresowej. Co chcesz zrobic?"<<endl;
            cout << "1. Logowanie"<<endl;
            cout << "2. Rejestracja"<<endl;
            cout << "3. Wyjscie"<<endl;
            cin>>wybor;

            switch (wybor){
            case '1':
                idUzytkownika = osoba.logowanie(daneDoLogowania);
                osobaZKsiazkiAdresowej.wczytajOsobyZPlikuDlaDanegoUzytkownika(ksiazkaAdresowa, idUzytkownika);
                break;
            case '2':
                osoba.rejestracja(daneDoLogowania);
                break;
            case '3':
                cout << "Dziekuje za skorzystanie z ksiazki adresowej. Do zobaczenia."<<endl;
                Sleep(2500);
                exit(0);
                break;
            default:
                cout << "Podano zly numer, wybierz ponownie."<<endl;
                Sleep(2500);
                break;
            }
        }

        else if (idUzytkownika!=0){
                system ("cls");
                cout << "1. Wprowadzenie nowej osoby do ksiazki"<<endl;
                cout << "2. Wyszukiwarka"<<endl;
                cout << "3. Usuniecie osoby z ksiazki adresowej"<<endl;
                cout << "4. Edytuj wybrany rekord"<<endl;
                cout << "5. Zmien haslo"<<endl;
                cout << "9. Wyloguj"<<endl;
                cin >> wybor;

                switch (wybor){
                case '1':
                    osobaZKsiazkiAdresowej.wprowadzanieNowychOsobDoKsiazki(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '2':
                    while (wybor!='9'){
                        system ("cls");
                        cout << "Wybierz rodzaj wyszukiwania"<<endl;
                        cout << "1. Wyszukiwanie po imieniu"<<endl;
                        cout << "2. Wyszukiwanie po nazwisku"<<endl;
                        cout << "3. Pokaz cala ksiazke adresowa"<<endl;
                        cout << "9. Wroc do wczesniejszego menu"<<endl;

                        cin >> wybor;
                        switch (wybor){
                        case '1':
                            osobaZKsiazkiAdresowej.wyszukiwaniePoImieniu (ksiazkaAdresowa);
                            break;
                        case '2':
                            osobaZKsiazkiAdresowej.wyszukiwaniePoNazwisku (ksiazkaAdresowa);
                            break;
                        case '3':
                            osobaZKsiazkiAdresowej.pokazWszystkich (ksiazkaAdresowa);
                            break;
                        case '9':
                            break;
                        default:
                            cout << "Podano zly numer, wybierz ponownie: "<<endl;
                            system ("Pause");
                            break;
                        }
                   }
                    break;
                case '3':
                    osobaZKsiazkiAdresowej.usuwanieRekorduZPliku (ksiazkaAdresowa, idUzytkownika);
                    break;
                case '4':
                    osobaZKsiazkiAdresowej.edytujRekord(ksiazkaAdresowa, idUzytkownika);
                    break;
                case '5':
                    osoba.zmianaHasla(daneDoLogowania, idUzytkownika);
                    break;
                case '9':
                    idUzytkownika=0;
                    cout << "Wylogowano.";
                    Sleep(3000);
                    break;
                default:
                    cout << "Podano zly numer, wybierz ponownie."<<endl;
                    Sleep(2500);
                    break;
                }
        }
    }
return 0;
}


