#include "Contact.h"
#include "ArrayTemplate.h"
#define LOAD_OR_CREATE 1 //load = 1; create = 0;
using namespace std;

int main() {
    srand(time(0));
    FILE* fileContacts;

    int nContacts = 1;
    Contact* arrContacts = nullptr;
#if LOAD_OR_CREATE == 0
    nContacts = 3;
    arrContacts = new Contact[3]{
        {"Ivanov Ivan", "380501475337", "380501475337", "Kharkiv, Street Pushkina 12, ap. 48", "idksomething.gmail.com", "10.08.1998"},
        {"Artemov Artem", "88005553535", "87001237676", "Kharkiv, Street Saltivska 50, ap. 12", "krutoybro69420", "01.01.1901"},
        {"Nikolay Nikolaev", "380725341234", "774488339805", "none", "none", "12.12.2012"}
    };
#else
    fileContacts = fopen("allContacts.bin", "rb");
    if(fileContacts == nullptr) cout << "Error!" << endl;
    else{
        fread(&nContacts, sizeof(int),1,fileContacts);
        arrContacts = new Contact[nContacts];

        for (int i = 0; i < nContacts; i++){
            arrContacts[i].loadFromBin(fileContacts);
        }fclose(fileContacts);
        cout << "Loaded successfully!" << endl;
    }
#endif

    int menu = 1;
    int tempN = 0;
    int id = -1;
    char tempik[75] = "none";
    while (menu != 0){
        cout << "+======================================\n";
        cout << "|\t\t MENU:\n";
        cout << "+======================================\n";
        cout << "|\t 1. Show all contacts.\n";
        cout << "|\t 2. Add a new contact.\n";
        cout << "|\t 3. Edit contact.\n";
        cout << "|\t 4. Search contact by phone number.\n";
        cout << "|\t 5. Delete contact by phone number.\n";
        cout << "|\t 6. Sort contacts by age.\n";
        cout << "+======================================\n";
        cout << "|\t 0. Save and exit.\n";
        cout << "+======================================\n";
        cin >> menu;

        switch (menu){
            case 1:{
                for (int i = 0; i < nContacts; i++) {
                    arrContacts[i].showCont();
                }break;
            }      
            case 2:{
                Contact temp;
                cin.ignore();
                temp.createCont();
                addItemBack(arrContacts, nContacts, temp);
                break;                
            }
            case 3:
                id = -1;
                cout << "Input contact number: " << endl; cin >> tempik;
                for (int i = 0; i < nContacts; i++){
                    if(strcmp(arrContacts[i].Hnumber, tempik)==0 || strcmp(arrContacts[i].Wnumber, tempik)==0)
                    id=i;
                }if (id == -1){
                    cout << "No contacts found by number: +" << tempik << endl;
                    break;
                }else{
                    tempN = -1;
                    cout << "|\t Write the number of the parameter name \n";
                    cout << "|\t 1. Name.\n";
                    cout << "|\t 2. Home number.\n";
                    cout << "|\t 3. Work number.\n";
                    cout << "|\t 4. Home address.\n";
                    cout << "|\t 5. Email.\n";
                    cout << "|\t 6. Birthday.\n";
                    cin >> tempN;
                    switch (tempN){
                    case 1:
                        cout << "Enter what you want to change the name & surname: " << arrContacts[id].name << endl;
                        cin >> tempik;
                        strcpy(arrContacts[id].name, tempik);
                        break;
                    case 2:
                        cout << "Enter what you want to change home number: +" << arrContacts[id].Hnumber << endl;
                        cin >> tempik;
                        strcpy(arrContacts[id].Hnumber, tempik);
                        break;
                    case 3:
                        cout << "Enter what you want to change work number: +" << arrContacts[id].Wnumber << endl;
                        cin >> tempik;
                        strcpy(arrContacts[id].Wnumber, tempik);
                        break;
                    case 4:
                        cout << "Enter what you want to change home address: " << arrContacts[id].home << endl;
                        cin >> tempik;
                        strcpy(arrContacts[id].home, tempik);
                        break;
                    case 5:
                        cout << "Enter what you want to change email: " << arrContacts[id].email << endl;
                        cin >> tempik;
                        strcpy(arrContacts[id].email, tempik);
                        break;
                    case 6:
                        cout << "Enter what you want to change birthday: " << arrContacts[id].birthdate << endl;
                        cin >> tempik;
                        strcpy(arrContacts[id].birthdate, tempik);
                        break;
                    default:
                        cout << "Parameter number not found." << endl;
                        break;
                    }
                    break;
                }
           case 4:
                id = -1;
                cout << "Input contact number: " << endl; cin >> tempik;
                for (int i = 0; i < nContacts; i++){
                    if(strcmp(arrContacts[i].Hnumber, tempik)==0 || strcmp(arrContacts[i].Wnumber, tempik)==0)
                    id=i;
                }if (id == -1){
                    cout << "No contacts found by number: +" << tempik << endl;
                    break;
                }else{
                    arrContacts[id].showCont();
                    break;
                }
            case 5:
                id = -1;
                cout << "Input contact number: " << endl; cin >> tempik;
                for (int i = 0; i < nContacts; i++){
                    if(strcmp(arrContacts[i].Hnumber, tempik)==0 || strcmp(arrContacts[i].Wnumber, tempik)==0)
                    id=i;
                }if (id == -1){
                    cout << "No contacts found by number: +" << tempik << endl;
                    break;
                }else{
                    cout << "Delete: " << arrContacts[id].name << endl;
                    deleteItem(arrContacts, nContacts, id);
                    break;
                }
            case 6:{
                for (int i = 0; i < nContacts - 1; i++) {
                    for (int j = 0; j < nContacts - i - 1; j++) {
                        if (arrContacts[j].convertDateToInt() > arrContacts[j+1].convertDateToInt()) {
                            Contact temp = arrContacts[j];
                            arrContacts[j] = arrContacts[j + 1];
                            arrContacts[j + 1] = temp;
                        }
                    }
                }cout << "Sorted successfully!" << endl; break;
            }
            default:
                cout << "Сommand not found, try entering a valid number." << endl;
                break;
    }}
    fileContacts = fopen("allContacts.bin", "wb");
    if(fileContacts == nullptr) cout << "Error!" << endl;
    else{
        fwrite(&nContacts, sizeof(int), 1, fileContacts);
        for (int i = 0; i < nContacts; i++){
            arrContacts[i].saveToBin(fileContacts);
        }fclose(fileContacts);
        cout << "Saved successfully!" << endl;
    }
    return 0;
}