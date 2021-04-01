//
// Created by torchtheo on 2021/3/29.
//

#include "User.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include <unistd.h>
#include <termios.h>
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
        cout << "请输入密码：";
        cin >> s;
        getchar();
        if (s != this->payPass) {
            if (i == 3) {
                cout << "3次输入密码错误，账户被冻结\n";
                break;
            }
            cout << "密码错误！您还有" << 3 - i << "次机会" << endl;
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
        cout << "请输入支付密码：";
        cin >> s;
        getchar();
        if (s != this->payPass) {
            if (i == 3) {
                cout << "3次机会密码错误，账户被冻结\n";
                break;
            }
            cout << "密码错误！您还有" << 3 - i << "次机会" << endl;
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
    cout << "请输入商品名称：";
    cin >> Mname;
    getchar();
    double price;
    cout << "请输入商品价格：";
    cin >> price;
    getchar();
    string introduction;
    cout << "请输入商品描述：";
    cin >> introduction;
    getchar();
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? to_string(1 + ltm->tm_mon) : "0" + to_string(1 + ltm->tm_mon)) + "-" + to_string(ltm->tm_mday);
    Commodity* c = new Commodity(MID, Mname, introduction, price, this->UID, date, 1, 0);
    cout << "请确认发布商品的信息无误" << endl;
    cout << "********************************************************************************************" << endl;
    cout << "商品名称：" << c->getName() << endl;
    cout << "商品价格：" << c->getPrice() << endl;
    cout << "商品描述：" << c->getIntroduction() << endl;
    cout << "********************************************************************************************" << endl << endl;
    cout << "您确认要发布该商品吗(y/n)\n";
    char choice;
    cin >> choice;
    getchar();
    if (choice == 'y') {
        cout << "商品发布成功!" << endl;
        this->commodities.push_back(c);
    }
    else if (choice == 'n')
        cout << "取消成功" << endl;
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
    cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户界面" << endl;
    cout << "======================================================================================" << endl;
}

void User::showInfo() {
    cout << "************************************\n";
    cout << "用户名：\t" << this->getUsername() << endl;
    cout << "联系方式：\t" << this->getContact() << endl;
    cout << "地址：\t\t" << this->getAddress() << endl;
    printf("钱包余额：\t%.1lf\n", this->getBalance());
    cout << "************************************\n";
}

void User::showInfoManage() {
    system("clear");
    cout << "==============================================\n";
    cout << "1.返回用户界面 2.修改信息 3.查看信息 4.充值\n";
    cout << "==============================================\n";
}

void User::showMenu() {
    system("clear");
    cout << "==================================================" << endl;
    cout << "1.注销登录 2.我是买家 3.我是卖家 4.个人信息管理" << endl;
    cout << "==================================================" << endl << endl;
    cout << "输入操作：";
}

void User::showPutUp() {
    cout << "您发布的商品清单如下" << endl;
    cout << "**********************************************************************************\n";
    cout << "ID\t\t名称\t\t\t价格\t上架时间\t商品状态\n";
    for (int i = 0; i < this->commodities.size(); i++) {
        if (this->commodities[i]->getOwnerID() == this->UID) {
            cout << this->commodities[i]->getMID() << "\t\t" << left << setw(24) << this->commodities[i]->getName() << "\t";
            printf("%.1lf\t", this->commodities[i]->getPrice());
            cout << this->commodities[i]->getDate() << "\t";
            if (this->commodities[i]->getStatus() == -1) {
                cout << "已下架\n";
            }
            else if (this->commodities[i]->getStatus() == 1) {
                cout << "销售中\n";
            }
            else if (this->commodities[i]->getStatus() == 0) {
                cout << "已售出\n";
            }
        }
    }
    cout << "**********************************************************************************\n";
}

void User::showVendorMenu() {
    system("clear");
    cout << "======================================================================================" << endl;
    cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户界面" << endl;
    cout << "======================================================================================" << endl;
}