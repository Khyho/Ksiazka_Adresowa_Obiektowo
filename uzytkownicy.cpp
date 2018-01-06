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

Uzytkownik::Uzytkownik (int i =0, string log="", string pas=""){
    idUzytkownika = i;
    login = log;
    haslo = pas;
}


