#include <iostream>
#include <cstdlib>
#include "RecipientsBook.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

RecipientsBook::RecipientsBook (int id=0,int userID=0, string name="", string surname="", string telephone="", string email="", string address="")
:Recipient(id,userID, name, surname, telephone, email, address){
    this -> id = id;
    this -> userID = userID;
    this -> name = name;
    this -> surname = surname;
    this -> telephone = telephone;
    this -> email = email;
    this -> address = address;
}

void RecipientsBook::loadPeopleFromAFileForTheLoggedinUser (vector <Recipient> &addressBook, int userID){
    RecipientsBook personFromAddressBook (0,0,"","","","","");
    int lineNumber=1;
    int counter = 0;
    string line;
    string auxiliaryRecord="";
    string auxiliaryWord="";
    fstream file;

    addressBook.clear();

    file.open("Address_Book.txt", ios::in);

    while (getline(file,line)){
        switch(lineNumber){
        case 1:
            auxiliaryRecord = line;
            for (int i = 0; i<auxiliaryRecord.length();i++){
                if (auxiliaryRecord[i]!=124){
                    auxiliaryWord+=auxiliaryRecord[i];
                } else if (auxiliaryRecord[i]==124){
                    counter++;
                    switch(counter){
                        case 1:
                            personFromAddressBook.id = atoi(auxiliaryWord.c_str());
                            auxiliaryWord ="";
                            break;
                        case 2:
                            personFromAddressBook.userID = atoi(auxiliaryWord.c_str());
                            auxiliaryWord ="";
                            break;
                        case 3:
                            personFromAddressBook.name = auxiliaryWord;
                            auxiliaryWord ="";
                            break;
                        case 4:
                            personFromAddressBook.surname = auxiliaryWord;
                            auxiliaryWord ="";
                            break;
                        case 5:
                            personFromAddressBook.email = auxiliaryWord;
                            auxiliaryWord = "";
                            break;
                        case 6:
                            personFromAddressBook.telephone = auxiliaryWord;
                            auxiliaryWord = "";
                            break;
                        case 7:
                            personFromAddressBook.address = auxiliaryWord;
                            auxiliaryWord = "";
                            break;
                    }
                }
            }
            break;

        }
        if (lineNumber==1 && personFromAddressBook.userID==userID){
            addressBook.push_back(personFromAddressBook);
            counter = 0;
            lineNumber=0;
        }
        else {
            counter = 0;
            lineNumber=0;
        }
        lineNumber++;
    }
    file.close();
}

void RecipientsBook::enteringNewRecipientsToTheAddressBook (vector <Recipient> &addressBook, int userID){
    RecipientsBook personFromAddressBook(0,0,"","","","","");
    int i=0;
    system ("cls");

    personFromAddressBook.id = specifyID(addressBook, userID);

    personFromAddressBook.userID = userID;

    cout << "Podaj Imie: "<<endl;
    cin>> personFromAddressBook.name;
    personFromAddressBook.name = changeCase(personFromAddressBook.name);
    cout <<"Podaj nazwisko: "<<endl;
    cin >> personFromAddressBook.surname;
    personFromAddressBook.surname = changeCase(personFromAddressBook.surname);
    while (i <addressBook.size()){
        if (addressBook[i].name == personFromAddressBook.name && addressBook[i].surname==personFromAddressBook.surname ){
            system ("cls");
            cout << "Taki uzytkownik juz istnieje. Wprowadz ponownie."<<endl;
            cout << "Podaj imie:"<<endl;
            cin>> personFromAddressBook.name;
            personFromAddressBook.name = changeCase(personFromAddressBook.name);
            cout <<"Podaj nazwisko:"<<endl;
            cin >> personFromAddressBook.surname;
            personFromAddressBook.surname = changeCase(personFromAddressBook.surname);
            i=0;
        }else{
            i++;
        }
    }
    cout <<"Podaj email: "<<endl;
    cin >> personFromAddressBook.email;
    cout <<"Podaj numer telefonu: "<<endl;
    cin.sync();
    getline(cin,personFromAddressBook.telephone);
    cout <<"Podaj adres: "<<endl;
    cin.sync();
    getline(cin,personFromAddressBook.address);

    addressBook.push_back(personFromAddressBook);

    savePeopleToAFile(personFromAddressBook, addressBook);

    cout << "Osoba zapisana w ksiazce adresowej pod numerem "<<personFromAddressBook.id<<endl;
    Sleep(3000);
}

string RecipientsBook::changeCase (string textToChange){
    transform(textToChange.begin(),textToChange.begin()+1,textToChange.begin(),::toupper);
    transform(textToChange.begin()+1,textToChange.end(),textToChange.begin()+1,::tolower);
return textToChange;
}

int RecipientsBook::specifyID (vector <Recipient> &addressBook, int userID){
    int id = 0;
    addressBook.clear();
    loadAllPeopleFromTheFile(addressBook);

    if (addressBook.empty()==true){
        id = 1;
    }
    else{
        id = addressBook.back().id + 1;
    }

    addressBook.clear();
    loadPeopleFromAFileForTheLoggedinUser (addressBook, userID);

    return id;
}

void RecipientsBook::loadAllPeopleFromTheFile (vector <Recipient> &addressBook){
    RecipientsBook personFromAddressBook(0,0,"","","","","");
    int lineNumber=1;
    int x=0;
    int counter = 0;
    string line;
    string auxiliaryRecord="";
    string auxiliaryWord="";
    fstream file;

    addressBook.clear();

    file.open("Address_Book.txt", ios::in);

    while (getline(file,line)){
        switch(lineNumber){
        case 1:
            auxiliaryRecord = line;
            for (int i = 0; i<auxiliaryRecord.length();i++){
                if (auxiliaryRecord[i]!=124){
                    auxiliaryWord+=auxiliaryRecord[i];
                } else if (auxiliaryRecord[i]==124){
                    counter++;
                    switch(counter){
                        case 1:
                            personFromAddressBook.id = atoi(auxiliaryWord.c_str());
                            auxiliaryWord ="";
                            break;
                        case 2:
                            personFromAddressBook.userID = atoi(auxiliaryWord.c_str());
                            auxiliaryWord ="";
                            break;
                        case 3:
                            personFromAddressBook.name = auxiliaryWord;
                            auxiliaryWord ="";
                            break;
                        case 4:
                            personFromAddressBook.surname = auxiliaryWord;
                            auxiliaryWord ="";
                            break;
                        case 5:
                            personFromAddressBook.email = auxiliaryWord;
                            auxiliaryWord = "";
                            break;
                        case 6:
                            personFromAddressBook.telephone = auxiliaryWord;
                            auxiliaryWord = "";
                            break;
                        case 7:
                            personFromAddressBook.address = auxiliaryWord;
                            auxiliaryWord = "";
                            break;
                    }
                }
            }
            break;

        }
        if (lineNumber==1){
            addressBook.push_back(personFromAddressBook);
            counter = 0;
            lineNumber=0;
        }
        lineNumber++;
    }
    file.close();
}

void RecipientsBook::savePeopleToAFile (Recipient personFromAddressBook, vector <Recipient> &addressBook){
    fstream file;
    file.open("Address_Book.txt", ios::out | ios::app);
    if (file.good()==false && addressBook.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    file<<personFromAddressBook.id<<"|"<<personFromAddressBook.userID<<"|"<<personFromAddressBook.name<<"|"<<personFromAddressBook.surname<<"|"<<personFromAddressBook.email<<"|"<<personFromAddressBook.telephone<<"|"<<personFromAddressBook.address<<"|"<<endl;
    file.close();
}

void RecipientsBook::searchByName (vector <Recipient> &addressBook){
    string theNameOfTheWantedRecipient = "";
    int numberOfRecipients = 0;

    system("cls");
    if (!addressBook.empty())
    {   cout << "Wyszukaj osoby o imieniu: ";
        cin >> theNameOfTheWantedRecipient;
        theNameOfTheWantedRecipient = changeCase(theNameOfTheWantedRecipient);

        for (vector <Recipient>::iterator  itr = addressBook.begin(); itr != addressBook.end(); itr++)
        {
            if (itr -> name == theNameOfTheWantedRecipient)
            {
                cout << endl;
                cout << "Id:                 " << itr -> id << endl;
                cout << "Imie:               " << itr -> name << endl;
                cout << "Nazwisko:           " << itr -> surname << endl;
                cout << "Numer Telefonu:     " << itr -> telephone << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> address << endl;
                numberOfRecipients++;
            }
        }
        if (numberOfRecipients == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << theNameOfTheWantedRecipient << " <<<";
            cout << " w ksiazce adresowej wynosi: " << numberOfRecipients << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void RecipientsBook::searchBySurname(vector <Recipient> &addressBook){
    string theSurnameOfTheWantedRecipient;
    int numberOfRecipients = 0;

    system("cls");
    if (!addressBook.empty())
    {   cout << "Wyszukaj adresatow o nazwisku: ";
        cin >> theSurnameOfTheWantedRecipient;
        theSurnameOfTheWantedRecipient = changeCase(theSurnameOfTheWantedRecipient);

        for (vector <Recipient>::iterator itr = addressBook.begin(); itr != addressBook.end(); itr++)
        {
            if (itr -> surname == theSurnameOfTheWantedRecipient)
            {
                cout << endl;
                cout << "Id:                 " << itr -> id << endl;
                cout << "Imie:               " << itr -> name << endl;
                cout << "Nazwisko:           " << itr -> surname << endl;
                cout << "Numer Telefonu:     " << itr -> telephone << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> address << endl;
                numberOfRecipients++;
            }
        }
        if (numberOfRecipients == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << theSurnameOfTheWantedRecipient << " <<<";
            cout << " w ksiazce adresowej wynosi: " << numberOfRecipients << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void RecipientsBook::viewAll (vector <Recipient> &addressBook){
    system("cls");
    if (!addressBook.empty())
    {
        for (vector <Recipient> :: iterator itr = addressBook.begin(); itr != addressBook.end(); itr++)
        {
            cout << "Id:                 " << itr -> id << endl;
            cout << "Imie:               " << itr -> name << endl;
            cout << "Nazwisko:           " << itr -> surname << endl;
            cout << "Numer telefonu:     " << itr -> telephone << endl;
            cout << "Email:              " << itr -> email << endl;
            cout << "Adres:              " << itr -> address << endl << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void RecipientsBook::removal (vector <Recipient> &addressBook, int idOfThePersonBeingRemoved, int userID){

    loadAllPeopleFromTheFile (addressBook);
    for (vector <Recipient>::iterator itr = addressBook.begin(); itr != addressBook.end(); itr++){
        if (itr -> id == idOfThePersonBeingRemoved){
            addressBook.erase(itr);
            cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
            savePeopleToTheFileByOverwritingTheFile(addressBook, userID);
            break;
        }
    }
}

void RecipientsBook::deletingRecord (vector <Recipient> &addressBook, int userID){
    int idOfThePersonBeingRemoved = 0;
    char sign;
    bool ifThereIsAnAddressee = false;

    system("cls");
    if (!addressBook.empty()){
        cout << "Podaj numer ID osoby do usuniecia: ";
        cin >> idOfThePersonBeingRemoved;

        if (cin.fail()){
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl;
            cin.clear();
            cin.sync();
        } else {
            for (vector <Recipient>::iterator itr = addressBook.begin(); itr != addressBook.end(); itr++){
                if (itr -> id == idOfThePersonBeingRemoved){
                    ifThereIsAnAddressee = true;
                    cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                    cin >> sign;
                    if (sign == 't'){
                        removal (addressBook, idOfThePersonBeingRemoved, userID);
                        break;
                    } else {
                        cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                        break;
                    }
                }
            }
            if (ifThereIsAnAddressee == false)
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

void RecipientsBook::savePeopleToTheFileByOverwritingTheFile (vector <Recipient> &addressBook, int userID){

    fstream file;
    int i=0;
    file.open("Address_Book.txt", ios::out);
    if (file.good()==false && addressBook.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    while (i<addressBook.size()){
    file<<addressBook[i].id<<"|"<<addressBook[i].userID<<"|"<<addressBook[i].name<<"|"<<addressBook[i].surname<<"|"<<addressBook[i].email<<"|"<<addressBook[i].telephone<<"|"<<addressBook[i].address<<"|"<<endl;
    i++;
    }
    file.close();

    addressBook.clear();

    loadPeopleFromAFileForTheLoggedinUser (addressBook, userID);
}

void RecipientsBook::updateTheRecordInTheAddressBook (vector <Recipient> &addressBook, int idOfTheSelectedRecipient, int choice){
    loadAllPeopleFromTheFile (addressBook);
    for (vector <Recipient>::iterator itr = addressBook.begin(); itr <= addressBook.end(); itr++){
        if (itr -> id == idOfTheSelectedRecipient){
            switch (choice){
                case '1':
                    cout << "Podaj nowe imie: ";
                    cin >> itr -> name;
                    itr -> name = changeCase(itr -> name);
                    cout << endl << "Imie zostalo zmienione" << endl << endl;
                    savePeopleToTheFileByOverwritingTheFile(addressBook, userID);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    cin >> itr -> surname;
                    itr -> surname = changeCase(itr -> surname);
                    cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                    savePeopleToTheFileByOverwritingTheFile(addressBook, userID);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    cin >> itr -> telephone;
                    cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                    savePeopleToTheFileByOverwritingTheFile(addressBook, userID);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    cin >> itr -> email;
                    cout << endl << "Email zostal zmieniony" << endl << endl;
                    savePeopleToTheFileByOverwritingTheFile(addressBook, userID);
                    break;
                case '5':
                    cout << "Podaj nowy adres zamieszkania: ";
                    cin >> itr -> address;
                    itr -> address = changeCase(itr -> address);
                    cout << endl << "Adres zostal zmieniony" << endl << endl;
                    savePeopleToTheFileByOverwritingTheFile(addressBook, userID);
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

void RecipientsBook::editRecord (vector <Recipient> &addressBook, int userID){
    int idOfTheSelectedRecipient = 0;
    char choice;
    bool ifThereIsAnAddressee = false;

    system("cls");
    if (!addressBook.empty())
    {   cout << "Podaj numer ID osoby do edycji: ";
        cin >> idOfTheSelectedRecipient;

        if (cin.fail())
        {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            for (vector <Recipient>::iterator itr = addressBook.begin(); itr <= addressBook.end(); itr++)
            {
                if (itr -> id == idOfTheSelectedRecipient)
                {
                    ifThereIsAnAddressee = true;

                    cout << "Jaka dane chcesz zmienic?"<<endl;
                    cout << "1. Imie"<<endl;
                    cout << "2. Nazwisko"<<endl;
                    cout << "3. Numer Telefonu"<<endl;
                    cout << "4. eMail"<<endl;
                    cout << "5. Adres"<<endl;
                    cout << "9. Cofnij"<<endl;
                    cin >> choice;

                    updateTheRecordInTheAddressBook(addressBook, idOfTheSelectedRecipient, choice);
                    loadPeopleFromAFileForTheLoggedinUser(addressBook, userID);
                }
            }
            if (ifThereIsAnAddressee == false)
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
