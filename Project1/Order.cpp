//
// Created by torchtheo on 2021/3/29.
//

#include "Order.h"
#include<iostream>
using namespace std;
Order::Order(Commodity *c, string TID, string date, string vendor, string buyer, int status) {
    this->c = c;
    this->buyerID = buyer;
    this->date = date;
    this->TID = TID;
    this->vendorID = vendor;
    this->status = status;
}

string Order::getVendorID()
{
    return this->vendorID;
}

string Order::getBuyerID()
{
    return this->buyerID;
}

string Order::getTID()
{
    return this->TID;
}

string Order::getDate()
{
    return this->date;
}

int Order::getStatus()
{
    return this->status;
}

Commodity* Order::getCommodity()
{
    return this->c;
}

Order::Order() {

}