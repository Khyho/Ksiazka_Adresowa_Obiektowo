#include <iostream>
#include <cstdlib>
#include "uzytkownicy.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class KsiazkaUzytkownikow :public Uzytkownik{



    void zapiszUzytkownikowWPliku (Uzytkownik uzytkownikProgramu, vector <Uzytkownik> &daneDoLogowania);
    void zapiszUzytkownikowWPlikuNadpisujacPlik (vector <Uzytkownik> &daneDoLogowania);

    public:
    KsiazkaUzytkownikow (int i, string log, string pas);
    bool wczytajUzytkownikowProgramu (vector <Uzytkownik> &daneDoLogowania,  int idUzytkownika);
    void rejestracja (vector <Uzytkownik> &daneDoLogowania);
    int logowanie (vector <Uzytkownik> &daneDoLogowania);
    void zmianaHasla (vector <Uzytkownik> &daneDoLogowania, int idUzytkownika);

};
