#include <winsock2.h>
#pragma once

class Player {
    int m_num;
    int m_sum;
    SOCKET m_connection;
public:
    Player();
    Player(int);
    int Turn(bool, int, int);
    int Add();
    int Drop(int);
    void SetNum(int, SOCKET);
};