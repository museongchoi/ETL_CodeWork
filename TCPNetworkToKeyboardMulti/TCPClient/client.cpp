#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <WinSock2.h>
#include <Windows.h>
#include <conio.h>
#include <process.h>
#include "Packet.h"
#include "Session.h"

#pragma comment(lib, "ws2_32")

Session MySession;
SOCKET MyID;


unsigned __stdcall RecvThread(void* Arg)
{
	Packet Data;

	SOCKET ClientSocket = *(SOCKET*)Arg;
	//[][] [][][][][][]
	while (true)
	{
		int RecvByte = recv(ClientSocket, (char*)&Length, sizeof(Length), MSG_WAITALL);

		Length = ntohs(Length);
		RecvByte = recv(ClientSocket, (char*)&Data, Length, MSG_WAITALL);

		if (RecvByte > 0)
		{
			MakeHostOrder(Data);

			switch ((ECommand)Data.Code)
			{
			case ECommand::PostLogin:
			{
				MyID = Data.Id;
			}
			break;
			case ECommand::Spawn:
			{
				SessionInfo NewSession(Data.X,
					Data.Y,
					Data.R,
					Data.G,
					Data.B);
				MySession.Insert(Data.Id, NewSession);
			}
			break;
			case ECommand::Set:
			{
				SessionInfo InSession(Data.X,
					Data.Y,
					Data.R,
					Data.G,
					Data.B);
				MySession.List[Data.Id] = InSession;
			}
			break;
			case ECommand::Destroy:
			{
				// 접속 종료한 클라이언트를 MySession에서 제거
				MySession.Remove(Data.Id);
			}
			break;
			}

			system("cls");

			for (auto CurrentSession : MySession.List)
			{
				COORD Pos;
				Pos.X = CurrentSession.second.X;
				Pos.Y = CurrentSession.second.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
				printf("*");
			}
		}
	}

	return 0;
}

unsigned __stdcall SendThread(void* Arg)
{

	return 0;
}


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

	HANDLE RecvHandle = (HANDLE)_beginthreadex(0, 0, RecvThread, (void*)&ClientSocket, 0, 0);

	while (true)
	{
		memset(&Data, 0, sizeof(Data));
		int KeyCode = _getch();

		Data.X = MySession.List[MyID].X;
		Data.Y = MySession.List[MyID].Y;
		Data.R = MySession.List[MyID].R;
		Data.G = MySession.List[MyID].G;
		Data.B = MySession.List[MyID].B;
		Data.Id = MyID;


		switch (KeyCode)
		{
		case 'w':
			Data.Code = (u_short)(ECommand::Up);
			break;
		case 's':
			Data.Code = (u_short)(ECommand::Down);
			break;
		case 'a':
			Data.Code = (u_short)(ECommand::Left);
			break;
		case 'd':
			Data.Code = (u_short)(ECommand::Right);
			break;
		}
		MakeNetworkOrder(Data);

		Length = htons(sizeof(Data));

		int SendSize = send(ClientSocket, (char*)&Length, sizeof(Length), 0);
		SendSize = send(ClientSocket, (char*)&Data, sizeof(Data), 0);
	}

	closesocket(ClientSocket);


	WSACleanup();


	return 0;
}