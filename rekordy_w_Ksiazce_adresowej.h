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

    public:
        int id, idUzytkownika;
        string imie, nazwisko, numerTelefonu, email, adres;


        Adresat (int , int , string , string, string, string, string);
};

