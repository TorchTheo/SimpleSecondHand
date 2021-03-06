//
// Created by torchtheo on 2021/3/29.
//

#include "User.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include <unistd.h>
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);

using namespace std;

User::User() {

}

User::User(string UID, string name, string password, int sex, string contact, string address, double balance, string payPass) {
    this->commodities.clear();
    this->orders.clear();
    this->UID = UID;
    this->username = name;
    this->password = password;
    this->sex = sex;
    this->contact = contact;
    this->address = address;
    this->balance = balance;
    this->payPass = payPass;
    ifstream ifs("Commodities.txt", ios::in);
    string MID1;
    string name1;
    string introduction1;
    double price1;
    string ownerID1;
    string date1;
    int status1;
    while(ifs>>MID1>>name1>>introduction1>>price1>>ownerID1>>date1>>status1) {
        if (ownerID1 == this->UID) {
            Commodity *c = new Commodity(MID1, name1, introduction1, price1, ownerID1, date1, status1, 0);
            this->commodities.push_back(c);
        }
        else {
            Commodity* c = new Commodity(MID1, name1, introduction1, price1, ownerID1, date1, status1, 1);
            this->commodities.push_back(c);
        }
    }
    ifs.close();
    ifs.open("Orders.txt", ios::in);
    string MID2, TID2, date2, vendorUID2, buyerUID2;
    double price2;
    while (ifs >> TID2 >> MID2 >> price2 >> date2 >> vendorUID2 >> buyerUID2) {
        Order *o;
        if (buyerUID2 == this->UID || vendorUID2 == this->UID) {
            Commodity* c = NULL;
            for (int i = 0; i < this->commodities.size(); i++) {
                if (MID2 == commodities[i]->getMID()) {
                    c = commodities[i];
                    break;
                }

            }
            if (buyerUID2 == this->UID)
                o = new Order(c, TID2, date2, vendorUID2, buyerUID2, 0);
            else if (vendorUID2 == this->UID)
                o = new Order(c, TID2, date2, vendorUID2, buyerUID2, 1);
            this->orders.push_back(o);
        }
    }
    ifs.close();
}

bool User::checkPassword() {
    bool flag = false;
    string s;
    for (int i = 1; i <= 3; i++) {
        cout << "??????????????????";
        cin >> s;
        getchar();
        if (s != this->payPass) {
            if (i == 3) {
                cout << "3???????????????????????????????????????\n";
                break;
            }
            cout << "????????????????????????" << 3 - i << "?????????" << endl;
        }
        else {
            flag = true;
            break;
        }
    }
    return flag;
}

bool User::checkPayPass() {
    bool flag = false;
    string s;
    for (int i = 1; i <= 3; i++) {
        cout << "????????????????????????";
        cin >> s;
        getchar();
        if (s != this->payPass) {
            if (i == 3) {
                cout << "3???????????????????????????????????????\n";
                break;
            }
            cout << "????????????????????????" << 3 - i << "?????????" << endl;
        }
        else {
            flag = true;
            break;
        }
    }
    return flag;
}

string User::getAddress() {
    return this->address;
}

double User::getBalance() {
    return this->balance;
}

Commodity* User::getCommodity(string id) {
    Commodity *c = NULL;
    for (int i = 0; i < this->commodities.size(); i++) {
        if (this->commodities[i]->getMID() == id) {
            c = this->commodities[i];
            break;
        }
    }
    return c;
}

vector<Commodity*>& User::getCommodities() {
    return this->commodities;
}

string User::getContact() {
    return this->contact;
}

string User::getID() {
    return this->UID;
}

vector<Order*> User::getOrders() {
    return this->orders;
}

string User::getPassword() {
    return this->password;
}

string User::getPayPass() {
    return this->payPass;
}

int User::getSex() {
    return this->sex;
}

string User::getUsername() {
    return this->username;
}

bool User::login(string username, string password) {
    if (this->password == password && this->username == username)
        return true;
    return false;
}

void User::pushOrder(Order* order) {
    this->orders.push_back(order);
}

Commodity* User::putUpCommodity(string MID) {
    string Mname;
    cout << "????????????????????????";
    cin >> Mname;
    getchar();
    double price;
    cout << "????????????????????????";
    cin >> price;
    getchar();
    string introduction;
    cout << "????????????????????????";
    cin >> introduction;
    getchar();
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? to_string(1 + ltm->tm_mon) : "0" + to_string(1 + ltm->tm_mon)) + "-" + to_string(ltm->tm_mday);
    Commodity* c = new Commodity(MID, Mname, introduction, price, this->UID, date, 1, 0);
    cout << "????????????????????????????????????" << endl;
    cout << "********************************************************************************************" << endl;
    cout << "???????????????" << c->getName() << endl;
    cout << "???????????????" << c->getPrice() << endl;
    cout << "???????????????" << c->getIntroduction() << endl;
    cout << "********************************************************************************************" << endl << endl;
    cout << "??????????????????????????????(y/n)\n";
    char choice;
    cin >> choice;
    getchar();
    if (choice == 'y') {
        cout << "??????????????????!" << endl;
        this->commodities.push_back(c);
    }
    else if (choice == 'n')
        cout << "????????????" << endl;
    PAUSE
    return c;
}

void User::setAddress(string address) {
    this->address = address;
}

void User::setBalance(double balance) {
    this->balance = balance;
}

void User::setContact(string contact) {
    this->contact = contact;
}

void User::setPassword(string password) {
    this->password = password;
}

void User::setPayPass(string payPass) {
    this->payPass = payPass;
}

void User::setUsername(string username) {
    this->username = username;
}

void User::showBuyerMenu() {
    system("clear");
    cout << "======================================================================================" << endl;
    cout << "1.?????????????????? 2.???????????? 3.???????????? 4.?????????????????? 5.???????????????????????? 6.??????????????????" << endl;
    cout << "======================================================================================" << endl;
}

void User::showInfo() {
    cout << "************************************\n";
    cout << "????????????\t" << this->getUsername() << endl;
    cout << "???????????????\t" << this->getContact() << endl;
    cout << "?????????\t\t" << this->getAddress() << endl;
    printf("???????????????\t%.1lf\n", this->getBalance());
    cout << "************************************\n";
}

void User::showInfoManage() {
    system("clear");
    cout << "==============================================\n";
    cout << "1.?????????????????? 2.???????????? 3.???????????? 4.??????\n";
    cout << "==============================================\n";
}

void User::showMenu() {
    system("clear");
    cout << "==================================================" << endl;
    cout << "1.???????????? 2.???????????? 3.???????????? 4.??????????????????" << endl;
    cout << "==================================================" << endl << endl;
    cout << "???????????????";
}

void User::showPutUp() {
    cout << "??????????????????????????????" << endl;
    cout << "**********************************************************************************\n";
    cout << "ID\t\t??????\t\t\t??????\t????????????\t????????????\n";
    for (int i = 0; i < this->commodities.size(); i++) {
        if (this->commodities[i]->getOwnerID() == this->UID) {
            cout << this->commodities[i]->getMID() << "\t\t" << left << setw(24) << this->commodities[i]->getName() << "\t";
            printf("%.1lf\t", this->commodities[i]->getPrice());
            cout << this->commodities[i]->getDate() << "\t";
            if (this->commodities[i]->getStatus() == -1) {
                cout << "?????????\n";
            }
            else if (this->commodities[i]->getStatus() == 1) {
                cout << "?????????\n";
            }
            else if (this->commodities[i]->getStatus() == 0) {
                cout << "?????????\n";
            }
        }
    }
    cout << "**********************************************************************************\n";
}

void User::showVendorMenu() {
    system("clear");
    cout << "======================================================================================" << endl;
    cout << "1.???????????? 2.?????????????????? 3.?????????????????? 4.???????????? 5.?????????????????? 6.??????????????????" << endl;
    cout << "======================================================================================" << endl;
}