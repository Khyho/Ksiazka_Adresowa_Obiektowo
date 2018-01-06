#include <iostream>
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

Adresat::Adresat (int i=0,int iU=0, string im="", string naz="", string nrTel="", string em="", string adr=""){
    id = i;
    idUzytkownika = iU;
    imie = im;
    nazwisko = naz;
    numerTelefonu = nrTel;
    email = em;
    adres = adr;
}


