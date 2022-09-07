// ClientB.cpp 
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#pragma warning(disable: 4996)
#define PORT 1000

using namespace std;

SOCKET Connection;
int PlayerNum;

void Chat() {
	int counter = 0;
	char msg[256];
	while (TRUE) {
		recv(Connection, msg, sizeof(msg), NULL);
		if (counter == 0) {
			PlayerNum = msg[0] - '0';
			counter++;
		}
		else {
			cout << msg << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUSSIAN");
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Ошибка" << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofSock = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Ошибка" << endl;
		return 1;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Chat, NULL, NULL, NULL);

	char msg1[256];
	while (TRUE) {
		cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
	}

	system("pause");
	return 0;
}