#include "Player.h"
#include <winsock2.h>
#include <vector>

class Game {
    int m_players;
    int m_table;
    int m_max;
    int m_turn;
    Player* m_ids;
    SOCKET* m_connections;
public:
    Game(int, int, int, SOCKET*);
    //    void ToTable(int);
    //    void FromTable(int);
    int GetMax();
    void Turn();
};