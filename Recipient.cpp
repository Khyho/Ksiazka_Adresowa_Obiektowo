#include <iostream>
#include "Recipient.h"
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

Recipient::Recipient (int id=0,int userID=0, string name="", string surname="", string telephone="", string email="", string address=""){
    this -> id = id;
    this -> userID = userID;
    this -> name = name;
    this -> surname = surname;
    this -> telephone = telephone;
    this -> email = email;
    this -> address = address;
}


