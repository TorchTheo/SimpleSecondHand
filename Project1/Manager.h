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
    void exitSystem();
    void findPass();
    void findPayPass();
    static Commodity* getCommodity(string MID);
    static string getMID();
    static string getTID();
    static string getUID();
    static User* getVendor(string UID);
    static void init();
    void IM(User* user);//信息管理
    void putDown(User* user);
    void query();
    static int queryInfo(string MID);//中间程序，通过MID查询商品
    void searchCommodity();//搜索商品
    static void showCommodities();//展示所有商品
    static void showMenu();//展示菜单
    static void showOrders();
    static void showUsers();
    void unfreeze();
    void userLogin();//用户登录
    void userRegister();
    void vendorAction(User* user);//卖家操作
    static void writeData();
    static vector<User*> users;
    static vector<Admin*> admins;
    static vector<Commodity*> commodities;
    static vector<Order*> orders;
};


#endif //PROJECT1_MANAGER_H
