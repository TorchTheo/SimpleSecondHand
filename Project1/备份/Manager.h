//
// Created by torchtheo on 2021/3/29.
//

#ifndef PROJECT1_MANAGER_H
#define PROJECT1_MANAGER_H
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Admin.h"
#include "User.h"
#include "Commodity.h"
using namespace std;

class Manager {
public:
    Manager();
    void adminLogin();//管理员登录
    void buyerAction(User* user);
    bool checkRegisterContact(string contact);
    bool checkRegisterPassword(string password);
    bool checkRegisterUsername(string username);
    bool checkUsername(string username);
    void delUser();
    void exitSystem();
    Commodity* getCommodity(string MID);
    string getMID();
    string getTID();
    string getUID();
    User* getVendor(string UID);
    void init();
    void IM(User* user);//信息管理
    void modifyCommodity(User* user);
    void modifyInfo(User* user);
    void purchase(User* user);//user购买商品
    void putDown(User* user);
    void putDown();
    void query();
    int queryInfo(string MID);//中间程序，通过MID查询商品
    void recharge(User* user);
    void searchCommodity();//搜索商品
    void showBuyerOrders(User* user);
    void showCommodities();//展示所有商品
    void showMenu();//展示菜单
    void showOrders();
    void showUsers();
    void showVendorOrders(User* user);
    void userLogin();//用户登录
    void userRegister();
    void vendorAction(User* user);//卖家操作
    void writeData();
private:
    vector<User*> users;
    vector<Admin*> admins;
    vector<Commodity*> commodities;
    vector<Order*> orders;
};


#endif //PROJECT1_MANAGER_H
