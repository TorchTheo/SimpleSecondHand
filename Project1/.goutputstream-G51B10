//
// Created by torchtheo on 2021/3/29.
//

#ifndef PROJECT1_USER_H
#define PROJECT1_USER_H
#include"Commodity.h"
#include"Order.h"
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class User {
public:
    User();
    User(string UID, string name, string password, int sex, string contact, string address, double balance, string payPass, bool isFrozen);
    bool checkPassword();
    bool checkPayPass();
    bool checkUsername(string username);
    void findPassword();
    void findPayPassword();
    string getAddress();
    double getBalance();
    Commodity* getCommodity(string id);
    vector<Commodity*>& getCommodities();
    string getContact();
    string getID();
    string getPassword();
    string getPayPass();
    int getSex();
    string getUsername();
    bool login(string username, string password);
    void modifyCommodity();
    void modifyInfo();
    void purchase();
    void pushOrder(Order* order);
    Commodity* putUpCommodity(string MID);
    void recharge();
    void setAddress(string address);
    void setBalance(double balance);
    void setContact(string contact);
    void setPassword(string password);
    void setPayPass(string payPass);
    void setUsername(string username);
    void showBuyerMenu();
    void showBuyerOrders();
    void showInfo();
    void showInfoManage();
    void showMenu();
    void showPutUp();
    void showVendorMenu();
    void showVendorOrders();
    bool isFrozen;
private:
    string UID;
    string password;
    int sex;
    string contact;
    string address;
    vector<Commodity*> commodities;
    vector<Order*> orders;
    double balance;
    string username;
    string payPass;
};

#endif //PROJECT1_USER_H
