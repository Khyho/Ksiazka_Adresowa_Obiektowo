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

    public:
    int idUzytkownika;
    string login, haslo;

    Uzytkownik (int i, string log, string pas);
};
