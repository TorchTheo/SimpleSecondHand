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
    User(string UID, string name, string password, int sex, string contact, string address, double balance, string payPass);
    bool checkPassword();
    bool checkPayPass();
    string getAddress();
    double getBalance();
    Commodity* getCommodity(string id);
    vector<Commodity*>& getCommodities();
    string getContact();
    string getID();
    vector<Order*> getOrders();
    string getPassword();
    string getPayPass();
    int getSex();
    string getUsername();
    bool login(string username, string password);
    void pushOrder(Order* order);
    Commodity* putUpCommodity(string MID);
    void setAddress(string address);
    void setBalance(double balance);
    void setContact(string contact);
    void setPassword(string password);
    void setPayPass(string payPass);
    void setUsername(string username);
    void showBuyerMenu();
    void showInfo();
    void showInfoManage();
    void showMenu();
    void showPutUp();
    void showVendorMenu();
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
    int status;//0 denotes frozen
};

#endif //PROJECT1_USER_H
