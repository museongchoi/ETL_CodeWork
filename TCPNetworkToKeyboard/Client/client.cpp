#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <WinSock2.h>
#include <conio.h>

#pragma comment(lib, "ws2_32")

enum class ECommand
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
};

unsigned short Length;

#pragma pack(push, 1)
typedef struct _packet
{
	unsigned short Code;
	unsigned short X;
	unsigned short Y;
} Packet;
#pragma pack(pop)

int main()
{
	Packet Data;

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ClientSock;
	memset(&ClientSock, 0, sizeof(ClientSock));
	ClientSock.sin_family = AF_INET;
	ClientSock.sin_addr.s_addr = inet_addr("127.0.0.1");
	ClientSock.sin_port = htons(30000);

	int Result = connect(ClientSocket, (SOCKADDR*)&ClientSock, sizeof(ClientSock));
	if (Result == SOCKET_ERROR)
	{
		printf("connect error %d\n", GetLastError());
		exit(-1);
	}

	while (true)
	{
		memset(&Data, 0, sizeof(Data));

		int KeyCode = _getch();

		switch (KeyCode)
		{
		case 'w':
			Data.Code = htons((u_short)(ECommand::Up));
			break;
		case 's':
			Data.Code = htons((u_short)(ECommand::Down));
			break;
		case 'a':
			Data.Code = htons((u_short)(ECommand::Left));
			break;
		case 'd':
			Data.Code = htons((u_short)(ECommand::Right));
			break;
		}

		Length = htons(sizeof(Data));

		int SendSize = send(ClientSocket, (char*)&Length, sizeof(Length), 0);
		SendSize = send(ClientSocket, (char*)&Data, sizeof(Data), 0);

		//[][] [][][][][][]
		int RecvByte = recv(ClientSocket, (char*)&Length, sizeof(Length), MSG_WAITALL);

		Length = ntohs(Length);
		RecvByte = recv(ClientSocket, (char*)&Data, Length, MSG_WAITALL);

		if (RecvByte > 0)
		{
			Data.Code = ntohs(Data.Code);
			Data.X = ntohs(Data.X);
			Data.Y = ntohs(Data.Y);


			system("cls");

			COORD Pos;
			Pos.X = Data.X;
			Pos.Y = Data.Y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
			printf("*");
		}
	}

	closesocket(ClientSocket);


	WSACleanup();


	return 0;
}