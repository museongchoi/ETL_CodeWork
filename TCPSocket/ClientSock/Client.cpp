#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	char Operator[5] = { '+', '-', '*', '/', '%' };
	//랜덤 숫자 생성
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 10000);
	std::uniform_int_distribution<int> dist2(0, 4);
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	for (int i = 0; i < 1000; ++i)
	{
		int FirstNumber = dist(mt); //rand() % 89 + 10
		int SecondNumber = dist(mt);
		int OperatorIndex = dist2(mt);
		char Message[100] = { 0, };

		//_itoa(FirstNumber, &Message[0], 10);
		//Message[2] = Operator[OperatorIndex];
		//_itoa(SecondNumber, &Message[3], 10);

		sprintf(Message, "%d%c%d", FirstNumber, Operator[OperatorIndex], SecondNumber);


		SOCKET ClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ClientSocket == SOCKET_ERROR)
		{
			printf("socket error %d\n", GetLastError());
			exit(-1);
		}

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

		int SendSize = send(ClientSocket, Message, (int)strlen(Message), 0);
		if (SendSize <= 0)
		{
			printf("send error or disconnected %d\n", GetLastError());
			exit(-1);
		}

		printf("%d %c %d = ", FirstNumber, Operator[OperatorIndex], SecondNumber);

		char Buffer[1024] = { 0, };
		int RecvSize = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
		if (RecvSize <= 0)
		{
			printf("recv error or disconnected %d\n", GetLastError());
			exit(-1);
		}

		printf("%s\n ", Buffer);

		closesocket(ClientSocket);
	}

	WSACleanup();


	return 0;
}