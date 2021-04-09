//
// Created by torchtheo on 2021/3/29.
//

#include <termios.h>
#include"Admin.h"
#include "Manager.h"
#include "User.h"
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);

using namespace std;

Admin::Admin() {

}

Admin::Admin(string name, string password) {
    this->name = name;
    this->password = password;
}

string Admin::getName()
{
    return this->name;
}

string Admin::getPassword()
{
    return this->password;
}

bool Admin::login(string name, string password)
{
    if (this->name == name && this->password == password)
        return true;
    return false;
}

void Admin::showMenu()
{
    system("clear");
    cout << "=======================================================================================================\n";
    cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销\n";
    cout << "=======================================================================================================\n";
}

void Admin::delUser() {
    Manager::showUsers();
    cout << "请输入您要删除的用户UID：";
    string UID;
    bool flag = false;
    int index = 0;
    cin >> UID;
    getchar();
    for (int i = 0; i < Manager::users.size(); i++)
        if (Manager::users[i]->getID() == UID) {
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
        User* user = Manager::users[index];
        vector<Commodity*> com = user->getCommodities();
        for (int i = 0; i < com.size(); i++)
            if (com[i]->getBelonging() == 0) {
                Commodity* c = Manager::getCommodity(com[i]->getMID());
                c->setStatus(-1);
                com[i]->setStatus(-1);
            }
        Manager::users.erase(Manager::users.begin() + index);
        cout << "*********删除成功*********" << endl;
        Manager::writeData();
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

void Admin::putDown() {
    Manager::showCommodities();
    cout << "请输入下架商品的MID\n";
    string MID;
    cin >> MID;
    getchar();
    Commodity* c = Manager::getCommodity(MID);
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
        Manager::writeData();
        Manager::init();
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
