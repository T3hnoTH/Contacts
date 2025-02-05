#pragma once
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

struct Contact{
    char name[35] = "none";
    char Hnumber[15] = "0";
    char Wnumber[15] = "0";
    char home[75] = "none";
    char email[40] = "none";
    char birthdate[11] = "01.01.1901";

    void createCont(){
        cout << "Enter the contact's name & surname:" << endl; cin.getline(name, 35);
        cout << "Enter the contact's home number: " << endl; cin >> Hnumber;
        cout << "Enter the contact's work number: " << endl; cin >> Wnumber;
        cin.ignore();
        cout << "Enter the contact's home address: " << endl; cin.getline(home, 75);
        cout << "Enter contact email: " << endl; cin.getline(email, 40);
        cout << "Enter the contact's birthday (Format DD.MM.YYYY, example - 01.01.1901): " << endl; cin.getline(birthdate, 11);
    }

    void showCont(){
        cout << "+======================================\n";
        cout << "|\tName:" << name << endl;
        cout << "|\tHome number: +" << Hnumber << endl;
        cout << "|\tWork number: +" << Wnumber << endl;
        cout << "|\tHome adress:" << home << endl;
        cout << "|\tEmail:" << email << endl;
        cout << "|\tBirthday:" << birthdate << endl;
    }

    void saveToBin(FILE* file){
        int legName = strlen(name) + 1;
        fwrite(&legName, sizeof(int), 1, file);
        fwrite(name, sizeof(char), legName, file);

        int legHnum = strlen(name) + 1;
        fwrite(&legHnum, sizeof(int), 1, file);
        fwrite(Hnumber, sizeof(char), legHnum, file);

        int legWnum = strlen(name) + 1;
        fwrite(&legWnum, sizeof(int), 1, file);
        fwrite(Wnumber, sizeof(char), legWnum, file);

        int legHome = strlen(home) + 1;
        fwrite(&legHome, sizeof(int), 1, file);
        fwrite(home, sizeof(char), legHome, file);

        int legEmail = strlen(email) + 1;
        fwrite(&legEmail, sizeof(int), 1, file);
        fwrite(email, sizeof(char), legEmail, file);

        int legBirthday = strlen(birthdate) + 1;
        fwrite(&legBirthday, sizeof(int), 1, file);
        fwrite(birthdate, sizeof(char), legBirthday, file);
        
    }

    void loadFromBin(FILE* file){
        int legName;
        fread(&legName, sizeof(int), 1, file);
        fread(name, sizeof(char), legName, file);

        fread(&Hnumber, sizeof(unsigned long long), 1, file);
        fread(&Wnumber, sizeof(unsigned long long), 1, file);

        int legHome;
        fread(&legHome, sizeof(int), 1, file);
        fread(home, sizeof(char), legHome, file);

        int legEmail;
        fread(&legEmail, sizeof(int), 1, file);
        fread(email, sizeof(char), legEmail, file);

        int legBirthday;
        fread(&legBirthday, sizeof(int), 1, file);
        fread(birthdate, sizeof(char), legBirthday, file);
    }
    int convertDateToInt() {
        int day = (birthdate[0] - '0') * 10 + (birthdate[1] - '0');
        int month = (birthdate[3] - '0') * 10 + (birthdate[4] - '0');
        int year = (birthdate[6] - '0') * 1000 + (birthdate[7] - '0') * 100 + (birthdate[8] - '0') * 10 + (birthdate[9] - '0');
        return year * 10000 + month * 100 + day;
}
};