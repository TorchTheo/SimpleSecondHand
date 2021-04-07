//
// Created by torchtheo on 2021/3/29.
//

#ifndef PROJECT1_ADMIN_H
#define PROJECT1_ADMIN_H

#include<iostream>
#include<string>
using namespace std;
class Admin {
public:
    Admin();
    Admin(string name, string password);
    string getName();
    string getPassword();
    bool login(string name, string password);
    void showMenu();
private:
    string name, password;
};


#endif //PROJECT1_ADMIN_H
