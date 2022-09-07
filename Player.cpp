#include <iostream>
#include <iostream>
#include "Player.h"
#include <string>
#include "Object.h"

using namespace std;

Player::Player() {
    m_num = -1;
    m_sum = 0;
}

Player::Player(int num) {
    m_num = num;
    m_sum = 0;
}

int Player::Turn(bool ability, int max, int table) {

    int result;
    Object::ShowObj(table, m_connection);
    char msg[256];
    string temp = to_string(table);
    strcpy_s(msg, "There is ");
    strcat_s(msg, temp.c_str());
    strcat_s(msg, " objects currently in the game.");
    send(m_connection, msg, sizeof(msg), NULL);

    if (ability) {
        char msg[256];
        strcpy_s(msg, "Input 0 if you want to add objects, or any other string if you want to drop objects");
        send(m_connection, msg, sizeof(msg), NULL);
        char answer[256];
        recv(m_connection, answer, sizeof(answer), NULL);
        if (answer[0] == '0') {
            result = this->Add();
        }
        else {
            result = this->Drop(max);
            table -= result;
        }
    }
    else {
        result = this->Drop(max);
        table -= result;
    }
    if (table <= 0) {
        result = -90;
    }

    temp = to_string(result);
    strcpy_s(msg, "Test ");
    strcat_s(msg, temp.c_str());
    strcpy_s(msg, "\n");
    send(m_connection, msg, sizeof(msg), NULL);


    return result;
}

int Player::Drop(int max) {
    char msg[256];
    strcpy_s(msg, "It is your turn!");
    send(m_connection, msg, sizeof(msg), NULL);
    char amount[256];
    recv(m_connection, amount, sizeof(amount), NULL);
    m_sum += (amount[0]-'0');
    strcpy_s(msg, "Your turn is over.");
    send(m_connection, msg, sizeof(msg), NULL);
    return  (amount[0] - '0');
}

int Player::Add() {
    char msg[256];
    string temp = to_string(round(m_sum / 4));
    strcpy_s(msg, "You can add up to ");
    strcat_s(msg, temp.c_str());
    strcat_s(msg, " objects.");
    send(m_connection, msg, sizeof(msg), NULL);
    char amount[256];
    recv(m_connection, amount, sizeof(amount), NULL);
    m_sum -= (amount[0]-'0');
    strcpy_s(msg, "Your turn is over.");
    send(m_connection, msg, sizeof(msg), NULL);
    return -(amount[0] - '0');
}

void Player::SetNum(int num, SOCKET connection) {
    m_connection = connection;
    m_num = num;
}
