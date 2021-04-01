//
// Created by torchtheo on 2021/3/29.
//

#ifndef PROJECT1_ORDER_H
#define PROJECT1_ORDER_H

#include<iostream>
#include"Commodity.h"
#include<string>
#include<cstdio>
using namespace std;
class Order {
public:
    Order();
    Order(Commodity* c, string TID, string date, string vendor, string buyer, int status);
    string getBuyerID();
    Commodity* getCommodity();
    string getDate();
    string getVendorID();
    int getStatus();
    string getTID();
private:
    Commodity *c;
    string TID;
    string date;
    string vendorID;
    string buyerID;
    int status;//0表示这是我买的 1表示这是我卖的 -1表示全局的
};


#endif //PROJECT1_ORDER_H
