//
// Created by torchtheo on 2021/3/29.
//

#include "Commodity.h"
#include<iostream>
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);
using namespace std;



Commodity::Commodity() {}

Commodity::Commodity(string MID, string name, string introduction, double price, string ownerID, string date, int status, int be) {
    this->MID = MID;
    this->name = name;
    this->introduction = introduction;
    this->price = price;
    this->ownerID = ownerID;
    this->date = date;
    this->status = status;
    this->belonging = be;
}

void Commodity::setStatus(int status) {
    this->status = status;
}

void Commodity::setName(string name) {
    this->name = name;
}

void Commodity::setPrice(double price) {
    this->price = price;
}

void Commodity::setIntro(string intro) {
    this->introduction = intro;
}

int Commodity::getBelonging() {
    return this->belonging;
}

string Commodity::getMID() {
    return this->MID;
}

string Commodity::getName() {
    return this->name;
}

string Commodity::getIntroduction() {
    return this->introduction;
}

double Commodity::getPrice() {
    return this->price;
}

string Commodity::getOwnerID() {
    return this->ownerID;
}

string Commodity::getDate() {
    return this->date;
}

int Commodity::getStatus() {
    return this->status;
}
