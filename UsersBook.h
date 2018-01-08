#include <iostream>
#include <cstdlib>
#include "User.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class UsersBook :public User{



    void saveUsersInTheFile (User uzytkownikProgramu, vector <User> &loginData);
    void saveUsersInTheFileByOverwritingTheFile (vector <User> &loginData);

    public:
    UsersBook (int, string, string);
    bool loadProgramUsers (vector <User> &loginData,  int userID);
    void registration (vector <User> &loginData);
    int log (vector <User> &loginData);
    void passwordChange (vector <User> &loginData, int userID);

};
