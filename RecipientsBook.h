#include <iostream>
#include <cstdlib>
#include "Recipient.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class RecipientsBook :public Recipient{

string changeCase (string textToChange);
int specifyID (vector <Recipient> &addressBook, int userID);
void loadAllPeopleFromTheFile (vector <Recipient> &addressBook);
void savePeopleToAFile (Recipient person, vector <Recipient> &addressBook);
void savePeopleToTheFileByOverwritingTheFile (vector <Recipient> &addressBook, int userID);
void updateTheRecordInTheAddressBook (vector <Recipient> &addressBook, int idWybranegoAdresata, int choice);
void removal (vector <Recipient> &addressBook, int idUsuwanejOsoby, int userID);

public:

RecipientsBook (int , int , string , string, string, string, string);
void loadPeopleFromAFileForTheLoggedinUser (vector <Recipient> &addressBook, int userID);
void enteringNewRecipientsToTheAddressBook (vector <Recipient> &addressBook, int userID);
void searchByName (vector <Recipient> &addressBook);
void searchBySurname(vector <Recipient> &addressBook);
void viewAll (vector <Recipient> &addressBook);
void deletingRecord (vector <Recipient> &addressBook, int userID);
void editRecord (vector <Recipient> &addressBook, int userID);
};
