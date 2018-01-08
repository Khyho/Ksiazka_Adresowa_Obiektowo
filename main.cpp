#include <iostream>
#include "UsersBook.h"
#include "RecipientsBook.h"
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
    vector <Recipient> addressBook;
    vector <User> loginData;

    RecipientsBook personFromAddressBook(0,0,"","","","","");
    UsersBook person(0,"","");

    char choice='0';
    int userID=0;
    int userCounter=0;

    while (person.loadProgramUsers(loginData, userCounter)==true){
    userCounter++;
    }


    while (true){
        if (userID==0){
            system ("cls");
            cout << "Witaj w ksiazce adresowej. Co chcesz zrobic?"<<endl;
            cout << "1. Logowanie"<<endl;
            cout << "2. Rejestracja"<<endl;
            cout << "3. Wyjscie"<<endl;
            cin>>choice;

            switch (choice){
            case '1':
                userID = person.log(loginData);
                personFromAddressBook.loadPeopleFromAFileForTheLoggedinUser(addressBook, userID);
                break;
            case '2':
                person.registration(loginData);
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

        else if (userID!=0){
                system ("cls");
                cout << "1. Wprowadzenie nowej osoby do ksiazki"<<endl;
                cout << "2. Wyszukiwarka"<<endl;
                cout << "3. Usuniecie osoby z ksiazki adresowej"<<endl;
                cout << "4. Edytuj wybrany rekord"<<endl;
                cout << "5. Zmien haslo"<<endl;
                cout << "9. Wyloguj"<<endl;
                cin >> choice;

                switch (choice){
                case '1':
                    personFromAddressBook.enteringNewRecipientsToTheAddressBook(addressBook, userID);
                    break;
                case '2':
                    while (choice!='9'){
                        system ("cls");
                        cout << "Wybierz rodzaj wyszukiwania"<<endl;
                        cout << "1. Wyszukiwanie po imieniu"<<endl;
                        cout << "2. Wyszukiwanie po nazwisku"<<endl;
                        cout << "3. Pokaz cala ksiazke adresowa"<<endl;
                        cout << "9. Wroc do wczesniejszego menu"<<endl;

                        cin >> choice;
                        switch (choice){
                        case '1':
                            personFromAddressBook.searchByName (addressBook);
                            break;
                        case '2':
                            personFromAddressBook.searchBySurname (addressBook);
                            break;
                        case '3':
                            personFromAddressBook.viewAll (addressBook);
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
                    personFromAddressBook.deletingRecord (addressBook, userID);
                    break;
                case '4':
                    personFromAddressBook.editRecord(addressBook, userID);
                    break;
                case '5':
                    person.passwordChange(loginData, userID);
                    break;
                case '9':
                    userID=0;
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


