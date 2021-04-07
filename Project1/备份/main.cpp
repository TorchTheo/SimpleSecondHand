#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include "Manager.h"
using namespace std;
#define PAUSE printf("Press Enter key to continue...\n"); fgetc(stdin);

int main() {
    Manager manager;
    int choice;
    while (1) {
        manager.init();
        manager.showMenu();
        cout << "输入操作:";
        cin >> choice;
        getchar();
        switch (choice) {
            case 1:
                manager.userLogin();
                break;
            case 2:
                manager.userRegister();
                break;
            case 3:
                manager.adminLogin();
                break;
            case 4:
                manager.exitSystem();
                break;
            default:
                cout << "请输入正确的操作序号" << endl;
                PAUSE
                break;
        }
        manager.writeData();
    }
    return 0;
}