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

    int wybor=0;
    int idUzytkownika=0;

    while (osoba.wczytajUzytkownikowProgramu(daneDoLogowania, idUzytkownika)==true){
    idUzytkownika++;
    }


    while (1){
        system ("cls");
        cout << "Witaj w ksiazce adresowej. Co chcesz zrobic?"<<endl;
        cout << "1. Logowanie"<<endl;
        cout << "2. Rejestracja"<<endl;
        cout << "3. Wyjscie"<<endl;
        cin>>wybor;

        if (wybor == 1){
            idUzytkownika = osoba.logowanie(daneDoLogowania);
            osobaZKsiazkiAdresowej.wczytajOsobyZPlikuDlaDanegoUzytkownika(ksiazkaAdresowa, idUzytkownika);
            while (idUzytkownika!=0){
                system ("cls");
                cout << "1. Wprowadzenie nowej osoby do ksiazki"<<endl;
                cout << "2. Wyszukiwarka"<<endl;
                cout << "3. Usuniecie osoby z ksiazki adresowej"<<endl;
                cout << "4. Edytuj wybrany rekord"<<endl;
                cout << "5. Zmien haslo"<<endl;
                cout << "6. Wyloguj"<<endl;
                cin >> wybor;
                if (wybor == 1){
                    osobaZKsiazkiAdresowej.wprowadzanieNowychOsobDoKsiazki(ksiazkaAdresowa, idUzytkownika);
                } else if (wybor == 2){
                    while (1){
                        int wybor2;
                        system ("cls");
                        cout << "Wybierz rodzaj wyszukiwania"<<endl;
                        cout << "1. Wyszukiwanie po imieniu"<<endl;
                        cout << "2. Wyszukiwanie po nazwisku"<<endl;
                        cout << "3. Pokaz cala ksiazke adresowa"<<endl;
                        cout << "9. Wroc do wczesniejszego menu"<<endl;

                        cin >> wybor2;

                        if (wybor2 == 1){
                            osobaZKsiazkiAdresowej.wyszukiwaniePoImieniu (ksiazkaAdresowa);
                        } else if (wybor2 == 2){
                            osobaZKsiazkiAdresowej.wyszukiwaniePoNazwisku (ksiazkaAdresowa);
                        } else if (wybor2 == 3){
                            osobaZKsiazkiAdresowej.pokazWszystkich (ksiazkaAdresowa);
                        } else if (wybor2 == 9){
                            break;
                        }else {
                            cout << "Podano zly numer, wybierz ponownie."<<endl;
                            Sleep(2500);
                        }
                    }
                } else if (wybor == 3){
                    osobaZKsiazkiAdresowej.usuwanieRekorduZPliku (ksiazkaAdresowa, idUzytkownika);
                } else if (wybor == 4){
                    osobaZKsiazkiAdresowej.edytujRekord(ksiazkaAdresowa, idUzytkownika);
                } else if (wybor == 5){
                    osoba.zmianaHasla(daneDoLogowania, idUzytkownika);
                } else if (wybor == 6){
                    idUzytkownika=0;
                    cout << "Wylogowano.";
                    Sleep(3000);
                    break;
                } else {
                    cout << "Podano zly numer, wybierz ponownie."<<endl;
                    Sleep(2500);
                }
            }
        }  else if (wybor == 2){
            osoba.rejestracja(daneDoLogowania);
        }  else if (wybor == 3){
            cout << "Dziekuje za skorzystanie z ksiazki adresowej. Do zobaczenia."<<endl;
            Sleep(2500);
            exit(0);
        } else {
            cout << "Podano zly numer, wybierz ponownie."<<endl;
            Sleep(2500);
        }
    }
    return 0;
}


