//
// Created by torchtheo on 2021/3/29.
//

#include "Manager.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <termios.h>
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);

using namespace std;

Manager::Manager() {

}

void Manager::adminLogin() {
    string name, password;
    cout << "请输入管理员用户名：";
    cin >> name;
    cout << "请输入密码：";
    cin >> password;
    getchar();
    Admin* admin = NULL;
    for (int i = 0; i < admins.size(); i++) {
        if (admins[i]->login(name, password)) {
            admin = admins[i];
            break;
        }
    }
    if (!admin) {
        cout << "用户名或密码错误\n";
        PAUSE
        return;
    }
    cout << "********** 登陆成功 **********" << endl;
    while (1) {
        admin->showMenu();
        int choice;
        cout << "输入选择：";
        cin >> choice;
        getchar();
        switch (choice)
        {
            case 1:
                this->showCommodities();
                PAUSE
                break;
            case 2:
                this->query();
                break;
            case 3:
                this->showOrders();
                PAUSE
                break;
            case 4:
                this->showUsers();
                PAUSE
                break;
            case 5:
                this->delUser();
                PAUSE
                break;
            case 6:
                this->putDown();
                PAUSE
                break;
            case 7:
                return;
            default:
                cout << "请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }
}

void Manager::buyerAction(User *user) {
    while (1) {
        user->showBuyerMenu();
        cout << "输入选择：";
        int choice;
        cin >> choice;
        getchar();
        switch (choice)
        {
            case 1:
                this->showCommodities();
                PAUSE
                break;
            case 2:
                this->purchase(user);
                break;
            case 3:
                this->searchCommodity();
                break;
            case 4:
                this->showBuyerOrders(user);
                break;
            case 5:
                this->query();
                break;
            case 6:
                return;
            default:
                cout << "请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }

    PAUSE
}

bool Manager::checkRegisterContact(string contact) {
    for (int i = 0; i < contact.size(); i++)
        if (!(contact[i] >= '0' && contact[i] <= '9')) {
            cout << "!!!联系方式仅能包含数字!!!\n";
            return false;
        }
    return true;
}

bool Manager::checkRegisterPassword(string password) {
    if (password.size() > 20) {
        cout << "!!!密码多于20位!!!" << endl;
        return false;
    }
    for (int i = 0; i < password.size(); i++) {
        if (!(password[i] >= '0' && password[i] <= '9') && !(password[i] >= 'a' && password[i] <= 'z')) {
            cout << "!!!密码只能包含数字和小写字母!!!\n";
            return false;
        }
    }
    return true;
}

bool Manager::checkRegisterUsername(string username) {

    if (username.size() > 10) {
        cout << "!!!用户名多于10位!!!" << endl;
        return false;
    }
    for (int i = 0; i < username.size(); i++) {
        if (username[i] >= '0' && username[i] <= '9') {
            cout << "!!!用户名不能含有数字!!!\n";
            return false;
        }

    }
    if (!checkUsername(username)) {
        cout << "!!!用户名已存在!!!" << endl;
        return false;
    }
    return true;

}

bool Manager::checkUsername(string username) {
    bool flag = true;
    for (int i = 0; i < this->users.size(); i++)
        if (username == this->users[i]->getUsername()) {
            flag = false;
            break;
        }
    return flag;
}

void Manager::delUser() {
    this->showUsers();
    cout << "请输入您要删除的用户UID：";
    string UID;
    bool flag = false;
    int index = 0;
    cin >> UID;
    getchar();
    for (int i = 0; i < this->users.size(); i++)
        if (this->users[i]->getID() == UID) {
            index = i;
            flag = true;
            break;
        }
    if (!flag) {
        cout << "!!!您所输入的用户ID不存在!!!\n";
        return;
    }
    char choice;
    cout << "您确定要删除此用户吗？这个用户的商品会全部下架(y/n)\n";
    cin >> choice;
    getchar();
    if (choice == 'y') {
        User* user = this->users[index];
        vector<Commodity*> com = user->getCommodities();
        for (int i = 0; i < com.size(); i++)
            if (com[i]->getBelonging() == 0) {
                Commodity* c = this->getCommodity(com[i]->getMID());
                c->setStatus(-1);
                com[i]->setStatus(-1);
            }
        this->users.erase(this->users.begin() + index);
        cout << "*********删除成功*********" << endl;
    }
    else
        cout << "取消删除\n";
    return;
}

void Manager::exitSystem() {
    cout << "欢迎下次使用" << endl;
    exit(0);
}

Commodity* Manager::getCommodity(string MID) {
    Commodity* c = NULL;
    for (int i = 0; i < this->commodities.size(); i++) {
        if (this->commodities[i]->getMID() == MID) {
            c = this->commodities[i];
            break;
        }
    }
    return c;
}

string Manager::getMID() {
    string s = this->commodities[this->commodities.size() - 1]->getMID();
    char _s[6];
    for (int i = 1; i < 6; i++)
        _s[i - 1] = s[i];
    int index = atoi(_s);
    index++;
    int len = 0, k = index;
    while (k) {
        len++;
        k = k / 10;
    }
    string mid("");
    mid.push_back('M');
    for (int i = 0; i < 5 - len; i++)
        mid.push_back('0');
    mid = mid + to_string(index);
    return mid;
}

string Manager::getTID() {
    string s = this->orders[this->orders.size() - 1]->getTID();
    char _s[6];
    for (int i = 1; i < 6; i++)
        _s[i - 1] = s[i];
    int index = atoi(_s);
    index++;
    int len = 0, k = index;
    while (k) {
        len++;
        k = k / 10;
    }
    string tid("");
    tid.push_back('T');
    for (int i = 0; i < 5 - len; i++)
        tid.push_back('0');
    tid = tid + to_string(index);
    return tid;
}

string Manager::getUID() {
    string s = this->users[this->users.size() - 1]->getID();
    char _s[6];
    for (int i = 1; i < 6; i++)
        _s[i - 1] = s[i];
    int index = atoi(_s);
    index++;
    int len = 0, k = index;
    while (k) {
        len++;
        k = k / 10;
    }
    string uid("");
    uid.push_back('U');
    for (int i = 0; i < 5 - len; i++)
        uid.push_back('0');
    uid = uid + to_string(index);
    return uid;
}

User* Manager::getVendor(string UID) {
    User* u = NULL;
    for(int i = 0; i < this->users.size(); i++)
        if (this->users[i]->getID() == UID) {
            u = this->users[i];
            break;
        }
    return u;
}

void Manager::init() {
    this->admins.clear();
    this->commodities.clear();
    this->orders.clear();
    this->users.clear();
    ifstream ifs("User.txt", ios::in);
    string name, password, UID, contact, address, payPass;
    int sex;
    double balance;
    while (ifs >> UID >> name >> password >> sex >> contact >> address >> balance >> payPass) {
        User* user = new User(UID, name, password, sex, contact, address, balance, payPass);
        this->users.push_back(user);
    }
    ifs.close();
    ifs.open("Admins.txt", ios::in);
    while (ifs >> name >> password) {
        Admin* admin = new Admin(name, password);
        this->admins.push_back(admin);
    }
    ifs.close();
    ifs.open("Commodities.txt", ios::in);
    string MID1;
    string name1;
    string introduction1;
    double price1;
    string ownerID1;
    string date1;
    int status1;
    while (ifs >> MID1 >> name1 >> introduction1 >> price1 >> ownerID1 >> date1 >> status1) {
        Commodity* c = new Commodity(MID1, name1, introduction1, price1, ownerID1, date1, status1, -1);
        this->commodities.push_back(c);
    }
    ifs.close();
    ifs.open("Orders.txt", ios::in);
    string MID2, TID2, date2, vendorUID2, buyerUID2;
    double price2;
    while (ifs >> TID2 >> MID2 >> price2 >> date2 >> vendorUID2 >> buyerUID2) {
        Order* o;
        Commodity* c = NULL;
        for (int i = 0; i < this->commodities.size(); i++) {
            if (MID2 == commodities[i]->getMID()) {
                c = commodities[i];
                break;
            }

        }
        o = new Order(c, TID2, date2, vendorUID2, buyerUID2, -1);
        this->orders.push_back(o);

    }
}

void Manager::IM(User* user) {
    while (1) {
        user->showInfoManage();
        cout << "输入选择：";
        int choice;
        cin >> choice;
        getchar();
        switch (choice)
        {
            case 1:
                return;
            case 2:
                this->modifyInfo(user);
                break;
            case 3:
                user->showInfo();
                PAUSE
                break;
            case 4:
                this->recharge(user);
                PAUSE
                break;
            default:
                cout << "请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }

}

void Manager::modifyCommodity(User* user) {
    user->showPutUp();
    string MID;
    cout << "*********************************************************************************************" << endl;
    cout << "请输入修改商品ID：";
    cin >> MID;
    getchar();
    Commodity* c = this->getCommodity(MID);
    Commodity* c1 = user->getCommodity(MID);
    if (!c) {
        cout << "您输入的商品ID不存在\n";
        PAUSE
        return;
    }
    if (c1->getBelonging() == 1) {
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
            c1->setPrice(price);
            c->setPrice(price);
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
            c1->setIntro(s);
            c->setIntro(s);
            cout << "修改成功！\n";
            cout << "*********************************************************************************************" << endl;
        }
        else {
            cout << "取消修改\n";
        }
    }
    else {
        cout << "属性不存在，修改失败\n";
        cout << "*********************************************************************************************" << endl;
    }
    PAUSE
    return;
}

void Manager::modifyInfo(User* user) {
    user->showInfo();
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
            for (int i = 0; i < this->users.size(); i++)
                if (this->users[i]->getID() != user->getID() && s == this->users[i]->getUsername()) {
                    flag = false;
                    break;
                }
            if (!flag) {
                cout << "用户名重复\n";
                PAUSE
                return;
            }
            cout << "是否修改？（y/n）\n";
            cin >> option;
            getchar();
            if (option == 'y') {
                user->setUsername(s);
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
                user->setContact(s);
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
                user->setAddress(s);
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
                user->setPayPass(s);
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
                user->setPassword(s);
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

void Manager::purchase(User *user) {
    this->showCommodities();
    cout << "输入您想购买的物品ID：";
    string id;
    cin >> id;
    getchar();
    Commodity* c2 = this->getCommodity(id);
    if (!c2) {
        cout << "您所输入的ID有误，商品不存在" << endl;
        PAUSE
        return;
    }
    if (c2->getOwnerID() == user->getID()) {
        cout << "对不起，您不可以购买自己的商品哦" << endl;
        PAUSE
        return;
    }
    int flag = this->queryInfo(id);
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
    printf("您的现有余额为：%.1lf\n", user->getBalance());
    cout << "*****************************************************************************" << endl;
    char choice;
    cout << "您确定要购买此商品吗?(y/n)" << endl;
    cin >> choice;
    getchar();
    if (choice == 'y') {
        if (user->getBalance() - c2->getPrice() < 0) {
            cout << "对不起，您的余额不足" << endl;
            return;
        }
        else
        {
            User *vendor = this->getVendor(c2->getOwnerID());
            time_t now = time(0);
            tm* ltm = localtime(&now);
            cout << "购买成功\n您的余额为：\t";
            c2->setStatus(0);
            user->setBalance(user->getBalance() - c2->getPrice());
            vendor->setBalance(vendor->getBalance() + c2->getPrice());
            printf("%.1lf\n", user->getBalance());
            string date = to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon) >= 10 ? to_string(1 + ltm->tm_mon) : "0" + to_string(1 + ltm->tm_mon)) + "-" + to_string(ltm->tm_mday);
            cout << "交易时间：\t" <<date<< endl;
            cout << "*****************************************************************************" << endl;
            string TID = this->getTID();
            Order* o1 = new Order(c2, TID, date, c2->getOwnerID(), user->getID(), 0);
            Order* o2 = new Order(c2, TID, date, c2->getOwnerID(), user->getID(), -1);
            user->pushOrder(o1);
            this->orders.push_back(o2);
            PAUSE

        }
    }
    else if (choice == 'n') {
        cout << "取消成功" << endl;
        PAUSE
    }
}

void Manager::putDown(User* user) {
    user->showPutUp();
    cout << "请输入您想要下架商品的ID：";
    string MID;
    cin >> MID;
    getchar();
    Commodity* c = this->getCommodity(MID);
    Commodity* c1 = user->getCommodity(MID);
    if (!c) {
        cout << "您输入的商品ID不存在\n";
        PAUSE
        return;
    }
    if (c1->getBelonging() == 1) {
        cout << "对不起，这件商品不属于您，您没有修改权限\n";
        PAUSE
        return;
    }
    if (c->getStatus() == -1) {
        cout << "对不起哦，这件商品已经下架了\n";
        PAUSE
        return;
    }
    cout << "请确认商品信息\n";
    cout << "**************************************************\n";
    cout << "商品ID：" << c->getMID() << endl;
    cout << "商品名称：" << c->getName() << endl;
    printf("商品价格：%.1lf\n", c->getPrice());
    cout << "商品描述：" << c->getIntroduction() << endl;
    cout << "**************************************************\n";
    cout << "是否下架该商品？（y/n）";
    char choice;
    cin >> choice;
    getchar();
    if (choice == 'y') {
        c->setStatus(-1);
        c1->setStatus(-1);
        cout << "下架成功\n";
    }
    else
        cout << "取消下架\n";
    PAUSE
    return;
}

void Manager::putDown() {
    this->showCommodities();
    cout << "请输入下架商品的MID\n";
    string MID;
    cin >> MID;
    getchar();
    Commodity* c = this->getCommodity(MID);
    if (!c) {
        cout << "您输入的商品ID不存在\n";
        return;
    }
    if (c->getStatus() == -1) {
        cout << "对不起哦，这件商品已经下架了\n";
        return;
    }
    cout << "请确认商品信息\n";
    cout << "**************************************************\n";
    cout << "商品ID：" << c->getMID() << endl;
    cout << "商品名称：" << c->getName() << endl;
    printf("商品价格：%.1lf\n", c->getPrice());
    cout << "商品描述：" << c->getIntroduction() << endl;
    cout << "**************************************************\n";
    cout << "是否下架该商品？（y/n）";
    char choice;
    cin >> choice;
    getchar();
    if (choice == 'y') {
        c->setStatus(-1);
        cout << "下架成功\n";
        this->writeData();
        this->init();
    }
    else
        cout << "取消下架\n";
    return;
}

void Manager::query() {
    this->showCommodities();
    cout << "请输入您要查询的商品ID：";
    string id;
    cin >> id;
    getchar();
    this->queryInfo(id);
    PAUSE
}

int Manager::queryInfo(string MID) {
    int flag = 2;//0表示已经售出 1表示仍然有货 -1表示下架
    Commodity *c;
    cout << "*****************************************************************************" << endl;
    for (int i = 0; i < this->commodities.size(); i++) {
        if (MID == this->commodities[i]->getMID()) {

            c = this->commodities[i];
            if (this->commodities[i]->getStatus() == -1) {
                cout << "对不起，商品已下架O^O" << endl;
                return -1;
            }
            cout << "名称：\t\t" << this->commodities[i]->getMID() << endl;
            cout << "描述：\t\t" << this->commodities[i]->getIntroduction() << endl;
            printf("价格：\t\t%.1lf\n", this->commodities[i]->getPrice());
            cout << "上架时间：\t" << this->commodities[i]->getDate() << endl;
            cout << "卖家ID：\t" << this->commodities[i]->getOwnerID() << endl;
            cout << "商品状态：\t";
            if (this->commodities[i]->getStatus() == 1) {
                flag = 1;
                cout << "销售中" << endl;
            }

            else if (this->commodities[i]->getStatus() == 0) {
                flag = 0;
                cout << "已售出" << endl;
            }


            break;
        }

    }
    cout << "*****************************************************************************" << endl;
    if (flag == 2)
        cout << "您所输入的ID有误，商品不存在" << endl;
    return flag;
}

void Manager::recharge(User *user) {
    cout << "您的当前余额为：" << user->getBalance() << endl;
    cout << "请输入充值数目：";
    double money;
    cin >> money;
    getchar();
    cout << "************************************************************\n";
    user->setBalance(money + user->getBalance());
    cout << "充值成功\n";
    printf("当前余额：%.1lf\n", user->getBalance());
}

void Manager::searchCommodity() {
    string key;
    cout << "输入关键字：";
    cin >> key;
    getchar();
    cout << "*******************************************************************************\n";
    int num = 0;
    for (int i = 0; i < this->commodities.size(); i++) {
        if (this->commodities[i]->getName().find(key) != -1) {
            num++;
            if (num == 1) {
                cout << "ID\t\t名称\t\t\t价格\t\t状态\n";
            }
            cout << this->commodities[i]->getMID() << "\t\t" << left << setw(24) << this->commodities[i]->getName()
                 << "\t" << this->commodities[i]->getPrice() << "\t\t";
            if (this->commodities[i]->getStatus() == -1) {
                cout << "已下架\n";
            }
            else if (this->commodities[i]->getStatus() == 1) {
                cout << "销售中\n";
            }
            else if (this->commodities[i]->getStatus() == 0) {
                cout << "已出售\n";
            }
        }
    }
    if (!num) {
        cout << "没有找到您想要的商品\n";
    }
    cout << "*******************************************************************************\n";
    PAUSE
}

void Manager::showBuyerOrders(User* user) {
    cout << "*************************************************************************************" << endl;
    cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (int i = 0; i < user->getOrders().size(); i++) {
        if (!user->getOrders()[i]->getStatus()) {
            cout << user->getOrders()[i]->getTID() << "\t\t"
                 << user->getOrders()[i]->getCommodity()->getMID() << "\t\t"
                 << user->getOrders()[i]->getDate() << "\t";
            printf("%.1lf\t\t", user->getOrders()[i]->getCommodity()->getPrice());
            cout << user->getOrders()[i]->getVendorID() << "\t\t"
                 << user->getOrders()[i]->getBuyerID() << endl;
        }
    }
    cout << "*************************************************************************************" << endl;
    PAUSE
}

void Manager::showCommodities() {
    cout << "***********************************************************************************************************************" << endl;
    cout << "ID\t\t名称\t\t\t\t价格\t\t上架时间\t\t卖家ID\t\t商品状态" << endl;
    for (int i = 0; i < this->commodities.size(); i++) {
        cout << this->commodities[i]->getMID() << "\t\t"
             << left << setw(24) << this->commodities[i]->getName() << "\t\t";
        printf("%.1lf\t\t", this->commodities[i]->getPrice());
        cout << this->commodities[i]->getDate() << "\t\t" << this->commodities[i]->getOwnerID();
        if (this->commodities[i]->getStatus() == 1)
            cout << "\t\t销售中\n";
        else if (this->commodities[i]->getStatus() == 0)
            cout << "\t\t已售出\n";
        else if (this->commodities[i]->getStatus() == -1)
            cout << "\t\t已下架\n";
    }
    cout << "***********************************************************************************************************************" << endl;
}

void Manager::showMenu(){
    system("clear");
    cout << "=================================================" << endl;
    cout << "1.用户登录 2.用户注册 3.管理员登录 4.退出程序" << endl;
    cout << "=================================================" << endl << endl;
}

void Manager::showOrders() {
    cout << "*************************************************************************************" << endl;
    cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (int i = 0; i < this->orders.size(); i++) {
        cout << this->orders[i]->getTID() << "\t\t"
             << this->orders[i]->getCommodity()->getMID() << "\t\t"
             << this->orders[i]->getDate() << "\t";
        printf("%.1lf\t\t", this->orders[i]->getCommodity()->getPrice());
        cout << this->orders[i]->getVendorID() << "\t\t"
             << this->orders[i]->getBuyerID() << endl;
    }
    cout << "*************************************************************************************" << endl;
}

void Manager::showUsers()
{
    cout << "*********************************************************************\n";
    cout << "UID\t用户名\t\t联系方式\t地址\t\t余额\n";
    for (int i = 0; i < users.size(); i++) {
        cout << users[i]->getID() << "\t"
             << users[i]->getUsername() << "\t\t"
             << users[i]->getContact() << "\t"
             << users[i]->getAddress() << "\t\t";
        printf("%.1lf\n", users[i]->getBalance());
    }
}

void Manager::showVendorOrders(User* user) {
    cout << "*************************************************************************************" << endl;
    cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (int i = 0; i < user->getOrders().size(); i++) {
        if (user->getOrders()[i]->getStatus() == 1) {
            cout << user->getOrders()[i]->getTID() << "\t\t"
                 << user->getOrders()[i]->getCommodity()->getMID() << "\t\t"
                 << user->getOrders()[i]->getDate() << "\t";
            printf("%.1lf\t\t", user->getOrders()[i]->getCommodity()->getPrice());
            cout << user->getOrders()[i]->getVendorID() << "\t\t"
                 << user->getOrders()[i]->getBuyerID() << endl;
        }
    }
    cout << "*************************************************************************************" << endl;
    PAUSE
}

void Manager::userLogin() {
    string username, password;
    cout << "请输入用户名: ";
    cin >> username;
    getchar();
    cout << "请输入密码: ";
    cin >> password;
    getchar();
    User *user = NULL;
    bool flag = false;
    for (int i = 0; i < this->users.size(); i++)
        if (users[i]->login(username, password)) {
            user = users[i];
            flag = true;
            break;
        }
    if(flag)
        cout << "********** 登陆成功 **********" << endl;
    else {
        cout << "用户名或密码错误，请重新选择" << endl;
        PAUSE
        return;
    }
    PAUSE
    while (1) {
        user->showMenu();
        int choice;
        cin >> choice;
        getchar();
        switch (choice)
        {
            case 1:
                return;
            case 2:
                this->buyerAction(user);
                break;
            case 3:
                this->vendorAction(user);
                break;
            case 4:
                this->IM(user);
                break;
            default:
                cout << "请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }

    PAUSE
}

void Manager::userRegister() {
    string username, password, contact, address, payPass;
    int sex;
    while (1) {
        cout << "请输入用户名（不超过10位的字母或汉字）：";
        cin >> username;
        getchar();
        if (checkRegisterUsername(username))
            break;
    }
    while (1) {
        cout << "请输入密码（不超过20个字符，只能为小写字母和数字）：";
        cin >> password;
        getchar();
        if (checkRegisterPassword(password)) {
            string check;
            cout << "请再次输入密码：";
            cin >> check;
            getchar();
            if(check == password)
                break;
            else
                cout << "两次密码不同，请重新输入\n";
        }

    }
    while (1) {
        cout << "请输入性别（1.男 2.女 0.不愿透露）";
        cin >> sex;
        getchar();
        if (sex == 1 || sex == 2 || sex == 0)
            break;
        else
            cout << "请输入正确的序号\n";
    }
    while (1) {
        cout << "请输入联系方式：";
        cin >> contact;
        getchar();
        if (this->checkRegisterContact(contact))
            break;
    }
    cout << "请输入地址：";
    cin >> address;
    getchar();
    while (1) {
        cout << "请输入支付密码：";
        cin >> payPass;
        getchar();
        string check;
        cout << "请再次输入支付密码：";
        cin >> check;
        getchar();
        if (check == payPass)
            break;
        else
            cout << "两次密码不同，请重新输入\n";
    }
    User* user = new User(this->getUID(), username, password, sex, contact, address, 0, payPass);
    this->users.push_back(user);
    cout << "**********************添加成功**********************\n";
    PAUSE
}

void Manager::vendorAction(User *user) {
    while (1) {
        user->showVendorMenu();
        cout << "输入操作序号：";
        int choice;
        cin >> choice;
        getchar();
        cout << endl;
        switch (choice)
        {
            case 1:
                this->commodities.push_back(user->putUpCommodity(this->getMID()));
                break;
            case 2:
                user->showPutUp();
                PAUSE
                break;
            case 3:
                this->modifyCommodity(user);
                break;
            case 4:
                this->putDown(user);
                break;
            case 5:
                this->showVendorOrders(user);
                break;
            case 6:
                return;
            default:
                cout << "请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }
}

void Manager::writeData() {
    ofstream ofs;
    ofs.open("User.txt", ios::out);
    for (int i = 0; i < this->users.size(); i++) {
        ofs << this->users[i]->getID()
            << " " << this->users[i]->getUsername()
            << " " << this->users[i]->getPassword()
            << " " << this->users[i]->getSex()
            << " " << this->users[i]->getContact()
            << " " << this->users[i]->getAddress()
            << " " << this->users[i]->getBalance()
            << " " << this->users[i]->getPayPass() << endl;
    }
    ofs.close();
    ofs.open("Admins.txt", ios::out);
    for (int i = 0; i < this->admins.size(); i++) {
        ofs << this->admins[i]->getName() << " "
            << this->admins[i]->getPassword() << endl;
    }
    ofs.close();
    ofs.open("Commodities.txt", ios::out);
    for (int i = 0; i < this->commodities.size(); i++) {
        ofs << this->commodities[i]->getMID() << " "
            << this->commodities[i]->getName() << " "
            << this->commodities[i]->getIntroduction() << " "
            << this->commodities[i]->getPrice() << " "
            << this->commodities[i]->getOwnerID() << " "
            << this->commodities[i]->getDate() << " "
            << this->commodities[i]->getStatus() << endl;
    }
    ofs.close();
    ofs.open("Orders.txt", ios::out);
    for (int i = 0; i < this->orders.size(); i++) {
        ofs << this->orders[i]->getTID() << " "
            << this->orders[i]->getCommodity()->getMID() << " "
            << this->orders[i]->getCommodity()->getPrice() << " "
            << this->orders[i]->getDate() << " "
            << this->orders[i]->getVendorID() << " "
            << this->orders[i]->getBuyerID() << endl;
    }
    ofs.close();
}