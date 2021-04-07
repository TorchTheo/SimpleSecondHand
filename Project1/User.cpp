//
// Created by torchtheo on 2021/3/29.
//

#include "User.h"
#include "Manager.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include <unistd.h>
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);

using namespace std;

vector<User*> Manager::users;
vector<Admin*> Manager::admins;
vector<Commodity*> Manager::commodities;
vector<Order*> Manager::orders;

User::User() {

}

User::User(string UID, string name, string password, int sex, string contact, string address, double balance, string payPass, bool isFrozen) {
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
    this->isFrozen = isFrozen;
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
                this->isFrozen = true;
                cout<<"账户即将注销....\n";
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

bool User::checkUsername(string username) {
    ifstream ifs("User.txt", ios::in);
    string name1, password1, UID1, contact1, address1, payPass1;
    int sex1;
    double balance1;
    bool isFrozen1;
    while (ifs >> UID1 >> name1 >> password1 >> sex1 >> contact1 >> address1 >> balance1 >> payPass1 >> isFrozen1) {
        if(UID1 != this->UID && username == this->username)
            return false;
    }
    ifs.close();
    return true;
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

void User::modifyCommodity() {
    this->showPutUp();
    string MID;
    cout << "*********************************************************************************************" << endl;
    cout << "请输入修改商品ID：";
    cin >> MID;
    getchar();
    Commodity* c1 = Manager::getCommodity(MID);
    Commodity* c = this->getCommodity(MID);
    if (!c) {
        cout << "您输入的商品ID不存在\n";
        PAUSE
        return;
    }
    if (c->getBelonging() == 1) {
        cout << "对不起，这件商品不属于您，您没有修改权限\n";
        PAUSE
        return;
    }
    cout << "请输入修改商品属性（1.名称 2.价格 3.描述）：";
    string s;
    double price = 0;
    int choice = 0;
    cin >> choice;
    getchar();
    if (choice == 1) {
        cout << "请输入修改后的商品名称：";
        cin >> s;
        getchar();
        cout << "\n请确认修改信息无误\n";
        cout << "****************************************\n";
        cout << "商品ID：" << c->getMID() << endl;
        cout << "商品名称：" << s << endl;
        printf("商品价格：%.1lf\n", c->getPrice());
        cout << "商品描述：" << c->getIntroduction() << endl;
        cout << "****************************************\n";
        char option;
        cout << "确认修改?(y/n)\n";
        cin >> option;
        getchar();
        if (option == 'y') {
            c->setName(s);
            c1->setName(s);
            cout << "修改成功！\n";
            cout << "*********************************************************************************************" << endl;
        }
        else {
            cout << "取消修改\n";
        }
    }
    else if (choice == 2) {
        cout << "请输入修改后的商品价格：";
        cin >> price;
        getchar();
        cout << "\n请确认修改信息无误\n";
        cout << "****************************************\n";
        cout << "商品ID：" << c->getMID() << endl;
        cout << "商品名称：" << c->getName() << endl;
        printf("商品价格：%.1lf\n", price);
        cout << "商品描述：" << c->getIntroduction() << endl;
        cout << "****************************************\n";
        char option;
        cout << "确认修改?(y/n)\n";
        cin >> option;
        getchar();
        if (option == 'y') {
            c->setPrice(price);
            c1->setPrice(price);
            cout << "修改成功！\n";
            cout << "*********************************************************************************************" << endl;
        }
        else {
            cout << "取消修改\n";
        }
    }
    else if (choice == 3) {
        cout << "请输入修改后的商品描述：";
        cin >> s;
        getchar();
        cout << "\n请确认修改信息无误\n";
        cout << "****************************************\n";
        cout << "商品ID：" << c->getMID() << endl;
        cout << "商品名称：" << c->getName() << endl;
        printf("商品价格：%.1lf\n", c->getPrice());
        cout << "商品描述：" << s << endl;
        cout << "****************************************\n";
        char option;
        cout << "确认修改?(y/n)\n";
        cin >> option;
        getchar();
        if (option == 'y') {
            c->setIntro(s);
            c1->setIntro(s);
            cout << "修改成功！\n";
            cout << "*********************************************************************************************" << endl;
        }
        else {
            cout << "取消修改\n";
            return;
        }
    }
    else {
        cout << "属性不存在，修改失败\n";
        cout << "*********************************************************************************************" << endl;
    }
    PAUSE
}

void User::modifyInfo() {
    this->showInfo();
    cout << "请选择你要修改的属性(1.用户名 2.联系方式 3.地址 4.支付密码 5.登录密码)：";
    string s;
    int choice;
    bool flag = true;
    char option;
    cin >> choice;
    getchar();
    switch (choice)
    {
        case 1:
            cout << "请输入修改后的用户名：";
            cin >> s;
            getchar();
            flag = checkUsername(s);
            if (!flag) {
                cout << "用户名重复\n";
                PAUSE
                return;
            }
            cout << "是否修改？（y/n）\n";
            cin >> option;
            getchar();
            if (option == 'y') {
                this->setUsername(s);
                cout << "修改成功\n";
                PAUSE
                return;
            }
            else {
                cout << "取消修改\n";
                PAUSE
                return;
            }
            break;
        case 2:
            cout << "请输入修改后的联系方式：";
            cin >> s;
            getchar();
            cout << "是否修改？（y/n）\n";
            cin >> option;
            getchar();
            if (option == 'y') {
                this->setContact(s);
                cout << "修改成功\n";
                PAUSE
                return;
            }
            else {
                cout << "取消修改\n";
                PAUSE
                return;
            }
            break;
        case 3:
            cout << "请输入修改后的地址：";
            cin >> s;
            getchar();
            cout << "是否修改？（y/n）\n";
            cin >> option;
            getchar();
            if (option == 'y') {
                this->setAddress(s);
                cout << "修改成功\n";
                PAUSE
                return;
            }
            else {
                cout << "取消修改\n";
                PAUSE
                return;
            }
            break;
        case 4:
            cout << "请输入修改后的支付密码：";
            cin >> s;
            getchar();
            cout << "是否修改？（y/n）\n";
            cin >> option;
            getchar();
            if (option == 'y') {
                this->setPayPass(s);
                cout << "修改成功\n";
                PAUSE
                return;
            }
            else {
                cout << "取消修改\n";
                PAUSE
                return;
            }
            break;
        case 5:
            cout << "请输入修改后的密码：";
            cin >> s;
            getchar();
            cout << "是否修改？（y/n）\n";
            cin >> option;
            getchar();
            if (option == 'y') {
                this->setPassword(s);
                cout << "修改成功\n";
                PAUSE
                return;
            }
            else {
                cout << "取消修改\n";
                PAUSE
                return;
            }
            break;
        default:
            cout << "请输入正确的操作序号" << endl;
            PAUSE
            break;
    }
}

void User::purchase() {
    Manager::showCommodities();
    cout << "输入您想购买的物品ID：";
    string id;
    cin >> id;
    getchar();
    Commodity* c = Manager::getCommodity(id);
    if (!c) {
        cout << "您所输入的ID有误，商品不存在" << endl;
        PAUSE
        return;
    }
    if (c->getOwnerID() == this->UID) {
        cout << "对不起，您不可以购买自己的商品哦" << endl;
        PAUSE
        return;
    }
    int flag = Manager::queryInfo(id);
    Commodity * c2 = getCommodity(id);
    if (flag == -1) {
        PAUSE
        return;
    }
    else if (flag == 0) {
        cout << "对不起，该商品已经售出" << endl;
        PAUSE
        return;
    }
    else if (flag == 2) {
        PAUSE
        return;
    }
    printf("您的现有余额为：%.1lf\n", this->balance);
    cout << "*****************************************************************************" << endl;
    char choice;
    cout << "您确定要购买此商品吗?(y/n)" << endl;
    cin >> choice;
    getchar();
    if (choice == 'y') {
        if (this->balance - c2->getPrice() < 0) {
            cout << "对不起，您的余额不足" << endl;
            return;
        }
        else
        {
            if(!checkPayPass()) {
                PAUSE
                return;
            }
            User *vendor = Manager::getVendor(c2->getOwnerID());
            time_t now = time(0);
            tm* ltm = localtime(&now);
            cout << "购买成功\n您的余额为：\t";
            c2->setStatus(0);
            c->setStatus(0);
            this->balance -= c2->getPrice();
            vendor->setBalance(vendor->getBalance() + c2->getPrice());
            printf("%.1lf\n", this->balance);
            string date = to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? to_string(1 + ltm->tm_mon) : "0" + to_string(1 + ltm->tm_mon)) + "-" + ((ltm->tm_mday) >= 10 ? to_string(ltm->tm_mday) : "0" + to_string(ltm->tm_mday));
            cout << "交易时间：\t" <<date<< endl;
            cout << "*****************************************************************************" << endl;
            string TID = Manager::getTID();
            Order* o1 = new Order(c2, TID, date, c2->getOwnerID(), this->UID, 0);
            Order* o2 = new Order(c, TID, date, c2->getOwnerID(), this->UID, -1);
            this->pushOrder(o1);
            Manager::orders.push_back(o2);
            PAUSE

        }
    }
    else if (choice == 'n') {
        cout << "取消成功" << endl;
        PAUSE
    }
}

void User::pushOrder(Order* order) {
    this->orders.push_back(order);
}

Commodity* User::putUpCommodity(string MID) {
    cout<<"输入-1来取消发布\n";
    string Mname;
    cout << "请输入商品名称（禁止使用空格等分隔符）：";
    cin >> Mname;
    getchar();
    if(Mname == "-1") {
        cout << "取消发布\n";
        PAUSE
        return nullptr;
    }
    double price;
    cout << "请输入商品价格：";
    cin >> price;
    getchar();
    if(price == -1) {
        cout << "取消发布\n";
        PAUSE
        return nullptr;
    }
    string introduction;
    cout << "请输入商品描述（禁止使用空格等分隔符）：";
    cin >> introduction;
    getchar();
    if(introduction == "-1") {
        cout << "取消发布\n";
        PAUSE
        return nullptr;
    }
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? to_string(1 + ltm->tm_mon) : "0" + to_string(1 + ltm->tm_mon)) + "-" + ((ltm->tm_mday) >= 10 ? to_string(ltm->tm_mday) : "0" + to_string(ltm->tm_mday));
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

void User::recharge() {
    cout << "您的当前余额为：" << this->balance << endl;
    cout << "请输入充值数目：";
    double money;
    cin >> money;
    getchar();
    cout << "************************************************************\n";
    if(money <= 0) {
        cout<<"充值金额不能为0或负数\n";
    }
    this->balance += money;
    cout << "充值成功\n";
    printf("当前余额：%.1lf\n", this->balance);
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

void User::showBuyerOrders() {
    cout << "*************************************************************************************" << endl;
    cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (int i = 0; i < this->orders.size(); i++) {
        if (!this->orders[i]->getStatus()) {
            cout << this->orders[i]->getTID() << "\t\t"
                 << this->orders[i]->getCommodity()->getMID() << "\t\t"
                 << this->orders[i]->getDate() << "\t";
            printf("%.1lf\t\t", this->orders[i]->getCommodity()->getPrice());
            cout << this->orders[i]->getVendorID() << "\t\t"
                 << this->orders[i]->getBuyerID() << endl;
        }
    }
    cout << "*************************************************************************************" << endl;
    PAUSE
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

void User::showVendorOrders() {
    cout << "*************************************************************************************" << endl;
    cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (int i = 0; i < this->orders.size(); i++) {
        if (this->orders[i]->getStatus() == 1) {
            cout << this->orders[i]->getTID() << "\t\t"
                 << this->orders[i]->getCommodity()->getMID() << "\t\t"
                 << this->orders[i]->getDate() << "\t";
            printf("%.1lf\t\t", this->orders[i]->getCommodity()->getPrice());
            cout << this->orders[i]->getVendorID() << "\t\t"
                 << this->orders[i]->getBuyerID() << endl;
        }
    }
    cout << "*************************************************************************************" << endl;
    PAUSE
}

void User::findPassword() {
    cout << "请输入您预留的联系方式：";
    string _contact;
    cin>>_contact;
    getchar();
    if(_contact == this->contact) {
        cout<<"*******验证成功*******\n请输入新的密码：";
        string pass;
        string check;
        cin>>pass;
        getchar();
        cout<<"请再次输入密码：";
        cin>>check;
        getchar();
        if(check == pass) {
            cout<<"*******密码已经重新设置*******\n";
            this->password = pass;
        }
        else
            cout<<"!!!两次输入密码不同，请重试!!!\n";
    }
    else
        cout<<"联系方式有误，重新设置密码失败\n";
    PAUSE
}

void User::findPayPassword() {
    cout << "请输入您预留的联系方式：";
    string _contact;
    cin>>_contact;
    getchar();
    if(_contact == this->contact) {
        cout<<"*******验证成功*******\n请输入新的支付密码：";
        string pass;
        string check;
        cin>>pass;
        getchar();
        cout<<"请再次输入支付密码：";
        cin>>check;
        getchar();
        if(check == pass) {
            cout<<"*******支付密码已经重新设置*******\n";
            this->password = pass;
        }
        else
            cout<<"!!!两次输入支付密码不同，请重试!!!\n";
    }
    else
        cout<<"联系方式有误，重新设置支付密码失败\n";
    PAUSE
}
