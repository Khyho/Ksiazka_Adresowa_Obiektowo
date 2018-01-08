#include <iostream>
#include <cstdlib>
#include "UsersBook.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;


UsersBook::UsersBook (int userID=0, string login="", string password=""):User(userID, login, password){
    this -> userID = userID;
    this -> login = login;
    this -> password = password;}

bool UsersBook::loadProgramUsers (vector <User> &loginData, int userID){

    UsersBook person (0, "", "");
    int lineNumber=userID+1;
    int currentNumber=1;
    int counter = 0;
    string line;
    string auxiliaryRecord="";
    string auxiliaryWord="";
    fstream file;

    file.open("Users.txt", ios::in);
    while (getline(file,line)){
        if (currentNumber == lineNumber){
            auxiliaryRecord = line;
            for (int i = 0; i<auxiliaryRecord.length();i++){
                if (auxiliaryRecord[i]!=124){
                    auxiliaryWord+=auxiliaryRecord[i];
                } else if (auxiliaryRecord[i]==124){
                    counter++;
                    switch(counter){
                        case 1:
                            person.userID = atoi(auxiliaryWord.c_str());
                            auxiliaryWord ="";
                            break;
                        case 2:
                            person.login = auxiliaryWord;
                            auxiliaryWord ="";
                            break;
                        case 3:
                            person.password = auxiliaryWord;
                            auxiliaryWord ="";
                            break;
                    }
                }
            }
        loginData.push_back(person);
        return true;
        }
        currentNumber++;
    }
    return false;
    file.close();
}

void UsersBook::registration (vector <User> &loginData) {
    UsersBook programUser (0, "", "");
    int i=0;
    system ("cls");
    if (loginData.empty()==true){
        programUser.userID = 1;
    }
    else{
        programUser.userID = loginData.back().userID + 1;
    }

    cout << "Podaj Login: "<<endl;
    cin>> programUser.login;

    cout <<"Podaj haslo: "<<endl;
    cin >> programUser.password;

    while (i <loginData.size()){
        if (loginData[i].login == programUser.login && loginData[i].password==programUser.password ){
            system ("cls");
            cout << "Taki uzytkownik juz istnieje. Wprowadz ponownie."<<endl;
            cout << "Podaj Login: "<<endl;
            cin>> programUser.login;

            cout <<"Podaj haslo: "<<endl;
            cin >> programUser.password;
            i=0;
        }else{
            i++;
        }
    }

    loginData.push_back(programUser);

    saveUsersInTheFile(programUser, loginData);

    cout << "Utworzono nowego uzytkownika o numerze "<<programUser.userID<<endl;
    Sleep(3000);

}

void UsersBook::saveUsersInTheFile (User programUser, vector <User> &loginData){
    fstream file;
    file.open("Users.txt", ios::out | ios::app);
    if (file.good()==false && loginData.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    file<<programUser.userID<<"|";
    file<<programUser.login<<"|";
    file<<programUser.password<<"|"<<endl;
    file.close();
}

int UsersBook::log (vector <User> &loginData){
    string login = "", password = "";

    vector <User>::iterator itr = loginData.begin();
    for (int attempts = 3; attempts > 0; attempts--){
            cout << "LOGOWANIE."<<endl;
            cout <<  "Podaj login: "<<endl;
            cin >> login;

            cout << "Podaj haslo: "<<endl;
            cin >> password;

            for (;itr != loginData.end();itr++){
                if (itr -> login == login && itr -> password == password){
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    return itr -> userID;
                }
            }
                cout << "Blednie podany login i/lub haslo."<<endl;
                cout <<"Pozostalo: "<<attempts-1<<" proby."<<endl;
                system("pause");
                itr = loginData.begin();
                system("cls");
    }
    cout << "Wprowadzono 3 razy bledne login i/lub haslo. Powrot do menu glownego." << endl;
    system("pause");
    return 0;
}

void UsersBook::passwordChange (vector <User> &loginData, int userID){
    string newPassword;
    cout << "Wprowadz nowe haslo: ";
    cin >> newPassword;
    vector <User>::iterator itr = loginData.begin()+userID-1;
    itr -> password = newPassword;
    saveUsersInTheFileByOverwritingTheFile(loginData);

}

void UsersBook::saveUsersInTheFileByOverwritingTheFile (vector <User> &loginData){
    fstream file;
    file.open("Users.txt", ios::out);
    if (file.good()==false && loginData.size()!=0){
        cout <<"plik nie istnieje!";
        exit(0);
    }
    for (vector <User>::iterator itr = loginData.begin(); itr != loginData.end(); itr++){
    file<<itr -> userID<<"|";
    file<<itr -> login<<"|";
    file<<itr -> password<<"|"<<endl;
    }
    file.close();
}
