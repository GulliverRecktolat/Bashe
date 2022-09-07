#include <winsock2.h>

class Object {
    SOCKET m_connection;
public:
    static void ShowObj(int, SOCKET);
};