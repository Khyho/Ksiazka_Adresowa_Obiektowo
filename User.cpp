#include <iostream>
#include "User.h"
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

User::User (int userID=0, string login="", string password=""){
    this -> userID = userID;
    this -> login = login;
    this -> password = password;
}


