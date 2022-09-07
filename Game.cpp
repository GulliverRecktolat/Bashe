#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include <string>
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include "player.h"
using namespace std;

Game::Game(int players, int objects, int max, SOCKET* connections) {
    m_connections = connections;
    m_players = players;
    m_table = objects;
    m_turn = 0;
    m_max = max;
    m_ids = new Player[m_players];
    for (int i = 0; i < m_players; i++) {
        m_ids[i].SetNum(i, connections[i]);
    }
}

void Game::Turn() {
    // выбор везунчика раз в m_players ходов
    int chosen = -1;
    if (m_turn % m_players == 0) {
        srand(time(NULL));
        chosen = rand() % m_players;
    }
    // текущий ход
    int current = m_turn % m_players;
    int result = m_ids[current].Turn(current == chosen, m_max, m_table);
    if (result == -90) {
        for (int i = 0; i < m_players; i++) {
            char msg[256];
            string temp = to_string(current);
            strcpy_s(msg, "Player number ");
            strcat_s(msg, temp.c_str());
            strcat_s(msg, " is loser.");
            send(m_connections[i], msg, sizeof(msg), NULL);
        }
        system("pause");
        exit(0);
    }
    if (result != -100) {
        m_table -= result;
    }
    m_turn++;
}

int Game::GetMax() {
    return m_max;
}
