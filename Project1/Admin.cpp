//
// Created by torchtheo on 2021/3/29.
//

#include <termios.h>
#include"Admin.h"
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);

using namespace std;

Admin::Admin() {

}

Admin::Admin(string name, string password) {
    this->name = name;
    this->password = password;
}

string Admin::getName()
{
    return this->name;
}

string Admin::getPassword()
{
    return this->password;
}

bool Admin::login(string name, string password)
{
    if (this->name == name && this->password == password)
        return true;
    return false;
}

void Admin::showMenu()
{
    system("clear");
    cout << "=======================================================================================================\n";
    cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销\n";
    cout << "=======================================================================================================\n";
}
