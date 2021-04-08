//
// Created by torchtheo on 2021/3/29.
//

#include "Manager.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <unistd.h>
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
                cin.clear();
                cin.sync();
                cout << "\n请输入正确的操作序号" << endl;
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
                user->purchase();
                if(user->isFrozen)
                    return;
                break;
            case 3:
                this->searchCommodity();
                break;
            case 4:
                user->showBuyerOrders();
                break;
            case 5:
                this->query();
                break;
            case 6:
                return;
            default:
                cin.clear();
                cin.sync();
                cout << "\n请输入正确的操作序号" << endl;
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
    for (int i = 0; i < users.size(); i++)
        if (username == users[i]->getUsername()) {
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
    for (int i = 0; i < users.size(); i++)
        if (users[i]->getID() == UID) {
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
        User* user = users[index];
        vector<Commodity*> com = user->getCommodities();
        for (int i = 0; i < com.size(); i++)
            if (com[i]->getBelonging() == 0) {
                Commodity* c = this->getCommodity(com[i]->getMID());
                c->setStatus(-1);
                com[i]->setStatus(-1);
            }
        users.erase(users.begin() + index);
        cout << "*********删除成功*********" << endl;
    }
    else if(choice == 'n')
        cout << "取消删除\n";
    else {
        cin.clear();
        cin.sync();
        cout<<"输入有误\n";
        PAUSE
    }
}

void Manager::exitSystem() {
    cout << "欢迎下次使用" << endl;
    exit(0);
}

void Manager::findPass() {
    cout<<"请输入您要找回密码的账号（UID或者用户名均可）：";
    string s;
    cin>>s;
    getchar();
    User *user = nullptr;
    for(User* u : users)
        if(u->getID() == s || u->getUsername() == s) {
            user = u;
            break;
        }
    if(!user) {
        cout<<"!!!帐号不存在!!!\n";
        PAUSE
        return;
    }
    user->findPassword();
}

void Manager::findPayPass() {
    cout<<"请输入您要找回支付密码的账号（UID或者用户名均可）：";
    string s;
    cin>>s;
    getchar();
    User *user = nullptr;
    for(User* u : users)
        if(u->getID() == s || u->getUsername() == s) {
            user = u;
            break;
        }
    if(!user) {
        cout<<"!!!帐号不存在!!!\n";
        PAUSE
        return;
    }
    user->findPayPassword();
}

Commodity* Manager::getCommodity(string MID) {
    Commodity* c = NULL;
    for (int i = 0; i < commodities.size(); i++) {
        if (commodities[i]->getMID() == MID) {
            c = commodities[i];
            break;
        }
    }
    return c;
}

string Manager::getMID() {
    if(commodities.empty())
        return "M00001";
    string s = commodities[commodities.size() - 1]->getMID();
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
    if(orders.empty())
        return "T00001";
    string s = orders[orders.size() - 1]->getTID();
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
    if(users.empty())
        return "U00001";
    string s = users[users.size() - 1]->getID();
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
    for(int i = 0; i < users.size(); i++)
        if (users[i]->getID() == UID) {
            u = users[i];
            break;
        }
    return u;
}

void Manager::init() {
    admins.clear();
    commodities.clear();
    orders.clear();
    users.clear();
    ifstream ifs("User.txt", ios::in);
    string name, password, UID, contact, address, payPass;
    int sex;
    double balance;
    bool isFrozen;
    while (ifs >> UID >> name >> password >> sex >> contact >> address >> balance >> payPass >> isFrozen) {
        User* user = new User(UID, name, password, sex, contact, address, balance, payPass, isFrozen);
        users.push_back(user);
    }
    ifs.close();
    ifs.open("Admins.txt", ios::in);
    while (ifs >> name >> password) {
        Admin* admin = new Admin(name, password);
        admins.push_back(admin);
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
        commodities.push_back(c);
    }
    ifs.close();
    ifs.open("Orders.txt", ios::in);
    string MID2, TID2, date2, vendorUID2, buyerUID2;
    double price2;
    while (ifs >> TID2 >> MID2 >> price2 >> date2 >> vendorUID2 >> buyerUID2) {
        Order* o;
        Commodity* c = nullptr;
        for (int i = 0; i < commodities.size(); i++) {
            if (MID2 == commodities[i]->getMID()) {
                c = commodities[i];
                break;
            }

        }
        o = new Order(c, TID2, date2, vendorUID2, buyerUID2, -1);
        orders.push_back(o);

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
                user->modifyInfo();
                break;
            case 3:
                user->showInfo();
                PAUSE
                break;
            case 4:
                user->recharge();
                PAUSE
                break;
            default:
                cin.clear();
                cin.sync();
                cout << "\n请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
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
    else if(choice == 'n')
        cout << "取消下架\n";
    else {
        cin.clear();
        cin.sync();
        cout<<"输入有误\n";
        PAUSE
    }
    PAUSE
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
    else if(choice == 'n')
        cout << "取消下架\n";
    else {
        cin.clear();
        cin.sync();
        cout<<"输入有误\n";
        PAUSE
    }
    PAUSE
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
    for (int i = 0; i < commodities.size(); i++) {
        if (MID == commodities[i]->getMID()) {

            c = commodities[i];
            if (commodities[i]->getStatus() == -1) {
                cout << "对不起，商品已下架O^O" << endl;
                return -1;
            }
            cout << "名称：\t\t" << commodities[i]->getMID() << endl;
            cout << "描述：\t\t" << commodities[i]->getIntroduction() << endl;
            printf("价格：\t\t%.1lf\n", commodities[i]->getPrice());
            cout << "上架时间：\t" << commodities[i]->getDate() << endl;
            cout << "卖家ID：\t" << commodities[i]->getOwnerID() << endl;
            cout << "商品状态：\t";
            if (commodities[i]->getStatus() == 1) {
                flag = 1;
                cout << "销售中" << endl;
            }

            else if (commodities[i]->getStatus() == 0) {
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

void Manager::searchCommodity() {
    string key;
    cout << "输入关键字：";
    cin >> key;
    getchar();
    cout << "*******************************************************************************\n";
    int num = 0;
    for (int i = 0; i < commodities.size(); i++) {
        if (commodities[i]->getName().find(key) != -1) {
            num++;
            if (num == 1) {
                cout << "ID\t\t名称\t\t\t价格\t\t状态\n";
            }
            cout << commodities[i]->getMID() << "\t\t" << left << setw(24) << commodities[i]->getName()
                 << "\t" << commodities[i]->getPrice() << "\t\t";
            if (commodities[i]->getStatus() == -1) {
                cout << "已下架\n";
            }
            else if (commodities[i]->getStatus() == 1) {
                cout << "销售中\n";
            }
            else if (commodities[i]->getStatus() == 0) {
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

void Manager::showCommodities() {
    cout << "***********************************************************************************************************************" << endl;
    cout << "ID\t\t名称\t\t\t\t价格\t\t上架时间\t\t卖家ID\t\t商品状态" << endl;
    for (int i = 0; i < commodities.size(); i++) {
        cout << commodities[i]->getMID() << "\t\t"
             << left << setw(24) << commodities[i]->getName() << "\t\t";
        printf("%.1lf\t\t", commodities[i]->getPrice());
        cout << commodities[i]->getDate() << "\t\t" << commodities[i]->getOwnerID();
        if (commodities[i]->getStatus() == 1)
            cout << "\t\t销售中\n";
        else if (commodities[i]->getStatus() == 0)
            cout << "\t\t已售出\n";
        else if (commodities[i]->getStatus() == -1)
            cout << "\t\t已下架\n";
    }
    cout << "***********************************************************************************************************************" << endl;
}

void Manager::showMenu(){
    system("clear");
    cout << "======================================================================================" << endl;
    cout << "1.用户登录 2.用户注册 3.管理员登录 4.账户解冻 5.忘记登录密码 6.忘记支付密码 7.退出程序" << endl;
    cout << "======================================================================================" << endl;
}

void Manager::showOrders() {
    cout << "*************************************************************************************" << endl;
    cout << "订单ID:\t\t商品ID：\t交易时间：\t交易金额：\t卖家ID：\t买家ID：\n";
    for (int i = 0; i < orders.size(); i++) {
        cout << orders[i]->getTID() << "\t\t"
             << orders[i]->getCommodity()->getMID() << "\t\t"
             << orders[i]->getDate() << "\t";
        printf("%.1lf\t\t", orders[i]->getCommodity()->getPrice());
        cout << orders[i]->getVendorID() << "\t\t"
             << orders[i]->getBuyerID() << endl;
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

void Manager::unfreeze() {
    cout<<"请输入您要解冻的账号（UID或者用户名均可）：";
    string s;
    cin>>s;
    getchar();
    User *user = nullptr;
    for(User* u : users)
        if(u->getID() == s || u->getUsername() == s) {
            user = u;
            break;
        }
    if(!user) {
        cout<<"!!!帐号不存在!!!\n";
        PAUSE
        return;
    }
    if(!user->isFrozen) {
        cout<<"*******您的账号并没有被冻结*******"<<endl;
        PAUSE
        return;
    }
    else {
        cout << "请输入您预留的联系方式：";
        string contact;
        cin>>contact;
        getchar();
        if(contact == user->getContact()) {
            cout<<"*******解冻成功*******\n";
            user->isFrozen = false;
            PAUSE
            return;
        }
        else {
            cout<<"联系方式有误，解冻失败\n";
            PAUSE
            return;
        }
    }
}

void Manager::userLogin() {
    string username, password;
    cout << "请输入用户名: ";
    cin >> username;
    getchar();
    cout << "请输入密码: ";
    cin >> password;
    getchar();
    User *user = nullptr;
    bool flag = false;
    for (int i = 0; i < users.size(); i++)
        if (users[i]->login(username, password)) {
            user = users[i];
            flag = true;
            break;
        }
    if(!flag) {
        cout << "用户名或密码错误，请重新选择" << endl;
        PAUSE
        return;
    }
    if(user->isFrozen) {
        cout << "对不起，您的账户已经被冻结..." << endl;
        PAUSE
        return;
    }
    cout << "********** 登陆成功 **********" << endl;
    PAUSE
    while (1) {
        if(user->isFrozen)
            return;
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
                cin.clear();
                cin.sync();
                cout << "\n请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }

    PAUSE
}

void Manager::userRegister() {
    cout<<"*******您可以输入-1来取消注册*******\n";
    string username, password, contact, address, payPass;
    int sex;
    while (1) {
        cout << "请输入用户名（不超过10位的字母或汉字）：";
        cin >> username;
        getchar();
        if(username == "-1") {
            cout<<"*******注册取消*******\n";
            PAUSE
            return;
        }
        if (checkRegisterUsername(username))
            break;
    }
    while (1) {
        cout << "请输入密码（不超过20个字符，只能为小写字母和数字）：";
        cin >> password;
        getchar();
        if(password == "-1") {
            cout<<"*******注册取消*******\n";
            PAUSE
            return;
        }
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
        if(sex == -1) {
            cout<<"*******注册取消*******\n";
            PAUSE
            return;
        }
        if (sex == 1 || sex == 2 || sex == 0)
            break;
        else
            cout << "请输入正确的序号\n";
    }
    while (1) {
        cout << "请输入联系方式：";
        cin >> contact;
        getchar();
        if(contact == "-1") {
            cout<<"*******注册取消*******\n";
            PAUSE
            return;
        }
        if (this->checkRegisterContact(contact))
            break;
    }
    cout << "请输入地址：";
    cin >> address;
    getchar();
    if(address == "-1") {
        cout<<"*******注册取消*******\n";
        PAUSE
        return;
    }
    while (1) {
        cout << "请输入支付密码：";
        cin >> payPass;
        getchar();
        if(payPass == "-1") {
            cout<<"*******注册取消*******\n";
            PAUSE
            return;
        }
        string check;
        cout << "请再次输入支付密码：";
        cin >> check;
        getchar();
        if(check == "-1") {
            cout<<"*******注册取消*******\n";
            PAUSE
            return;
        }
        if (check == payPass)
            break;
        else
            cout << "两次密码不同，请重新输入\n";
    }
    User* user = new User(this->getUID(), username, password, sex, contact, address, 0, payPass, false);
    users.push_back(user);
    cout << "**********************注册成功**********************\n";
    PAUSE
}

void Manager::vendorAction(User *user) {
    while (1) {
        Commodity* c = nullptr;
        user->showVendorMenu();
        cout << "输入操作序号：";
        int choice;
        cin >> choice;
        getchar();
        cout << endl;
        switch (choice)
        {
            case 1:
                c = user->putUpCommodity(getMID());
                if(!c)
                    break;
                commodities.push_back(c);
                break;
            case 2:
                user->showPutUp();
                PAUSE
                break;
            case 3:
                user->modifyCommodity();
                break;
            case 4:
                this->putDown(user);
                break;
            case 5:
                user->showVendorOrders();
                break;
            case 6:
                return;
            default:
                cin.clear();
                cin.sync();
                cout << "\n请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
    }
}

void Manager::writeData() {
    ofstream ofs;
    ofs.open("User.txt", ios::out);
    for (auto & user : users) {
        ofs << user->getID()
            << " " << user->getUsername()
            << " " << user->getPassword()
            << " " << user->getSex()
            << " " << user->getContact()
            << " " << user->getAddress()
            << " " << user->getBalance()
            << " " << user->getPayPass()
            << " " << user->isFrozen << endl;
    }
    ofs.close();
    ofs.open("Admins.txt", ios::out);
    for (auto & admin : admins) {
        ofs << admin->getName() << " "
            << admin->getPassword() << endl;
    }
    ofs.close();
    ofs.open("Commodities.txt", ios::out);
    for (auto & commodity : commodities) {
        ofs << commodity->getMID() << " "
            << commodity->getName() << " "
            << commodity->getIntroduction() << " "
            << commodity->getPrice() << " "
            << commodity->getOwnerID() << " "
            << commodity->getDate() << " "
            << commodity->getStatus() << endl;
    }
    ofs.close();
    ofs.open("Orders.txt", ios::out);
    for (auto & order : orders) {
        ofs << order->getTID() << " "
            << order->getCommodity()->getMID() << " "
            << order->getCommodity()->getPrice() << " "
            << order->getDate() << " "
            << order->getVendorID() << " "
            << order->getBuyerID() << endl;
    }
    ofs.close();
}


