//
// Created by torchtheo on 2021/3/29.
//

#ifndef PROJECT1_COMMODITY_H
#define PROJECT1_COMMODITY_H

#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

class Commodity {
public:
    Commodity();
    Commodity(string MID, string name, string introduction, double price, string ownerID, string date, int status, int be);
    int getBelonging();
    string getDate();
    string getIntroduction();
    string getMID();
    string getName();
    string getOwnerID();
    double getPrice();
    int getStatus();
    void setIntro(string intro);
    void setName(string name);
    void setPrice(double price);
    void setStatus(int status);

private:
    string MID;
    string name;
    string introduction;
    double price;
    string ownerID;
    string date;
    int status;//-1下架 1销售中 0已售出
    int belonging;//0属于我 1不属于我 -1表示全局
};


#endif //PROJECT1_COMMODITY_H
