#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <string>
#include "Game.h"
#include "Object.h"
#include "Player.h"
#pragma warning(disable: 4996)
#define PORT 1000

using namespace std;

SOCKET Connections[10];
int counter = 0, Num, Obj, OneTime;
/*
void Chat(int index) {
	char msg[256];
	while (true) {
		recv(Connections[index], msg, sizeof(msg), NULL);
		for (int i = 0; i < counter; i++) {
			if (i == index) {
				continue;
			}
			send(Connections[i], msg, sizeof(msg), NULL);
		}
	}
}
*/
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUSSIAN");
	

	cout << "Введите количество игроков ";
	cin >> Num;
	cout << "Введите количество предметов ";
	cin >> Obj;
	cout << "Введите количество предметов, которое можно взять за раз ";
	cin >> OneTime;
	while(OneTime > Obj) {
		cout << "Введите корректное предметов, которое можно взять за раз ";
		cin >> OneTime;
	}

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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET NewConnection;

	for (int i = 0; i < Num; i++) {
		NewConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofSock);
		cout << NewConnection << endl;
		if (NewConnection == 0) {
			cout << "Ошибка" << endl;
		}
		else {
			cout << "Игрок " << i << " подключился" << endl;

			string str1 = to_string(i);
			char msg[256];
			strcpy(msg, str1.c_str());
			send(NewConnection, msg, sizeof(msg), NULL);

			string temp = to_string(i);
			strcpy(msg, "You are player number ");
			strcat(msg, temp.c_str());
			send(NewConnection, msg, sizeof(msg), NULL);

			temp = to_string(Num);
			strcpy(msg, "There are ");
			strcat(msg, temp.c_str());
			strcat(msg, " players in the game.");
			send(NewConnection, msg, sizeof(msg), NULL);

			temp = to_string(Obj);
			strcpy(msg, "There are ");
			strcat(msg, temp.c_str());
			strcat(msg, " objects in the game.");
			send(NewConnection, msg, sizeof(msg), NULL);

			temp = to_string(OneTime);
			strcpy(msg, "You can drop up to ");
			strcat(msg, temp.c_str());
			strcat(msg, " objects per turn.");
			send(NewConnection, msg, sizeof(msg), NULL);

			Connections[i] = NewConnection;
			counter++;
			//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Chat, (LPVOID)(i), NULL, NULL);
		}
	}

	char msg[256] = "All players are connected. The game begins now!";
	for (int i = 0; i < counter; i++) {
		send(Connections[i], msg, sizeof(msg), NULL);
	}

	Game newGame(Num, Obj, OneTime, Connections);

	while (TRUE) {
		newGame.Turn();
	}
	
	system("pause");
	return 0;
}