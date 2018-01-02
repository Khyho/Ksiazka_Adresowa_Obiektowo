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

class Uzytkownik{

    int idUzytkownika;
    string login, haslo;

    void zapiszUzytkownikowWPliku (Uzytkownik uzytkownikProgramu, vector <Uzytkownik> &daneDoLogowania);
    void zapiszUzytkownikowWPlikuNadpisujacPlik (vector <Uzytkownik> &daneDoLogowania);

    public:
    Uzytkownik (int, string, string);
    bool wczytajUzytkownikowProgramu (vector <Uzytkownik> &daneDoLogowania,  int idUzytkownika);
    void rejestracja (vector <Uzytkownik> &daneDoLogowania);
    int logowanie (vector <Uzytkownik> &daneDoLogowania);
    void zmianaHasla (vector <Uzytkownik> &daneDoLogowania, int idUzytkownika);



};
