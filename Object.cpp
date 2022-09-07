#include <iostream>
#include "Object.h"
#include <string>
using namespace std;

void Object::ShowObj(int amount, SOCKET connection) {
    for (int i = 0; i < amount; i++) {
        char msg[256];
        strcpy_s(msg, "*");
        send(connection, msg, sizeof(msg), NULL);
    }
}

