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

class Recipient {

    public:
        int id, userID;
        string name, surname, telephone, email, address;


        Recipient (int, int, string, string, string, string, string);
};

