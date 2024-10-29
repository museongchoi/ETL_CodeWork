#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <time.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

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

	srand((unsigned int)time(NULL));
	int randNum1 = rand() % 100;
	int randNum2 = rand() % 100;
	int operation = rand() % 4;
	char operationChar;

	switch (operation)
	{
	case 0:
		operationChar = '+';
		break;
	case 1:
		operationChar = '-';
		break;
	case 2:
		operationChar = '*';
		break;
	case 3:
		operationChar = '/';
		break;
	}

	// 두 개의 숫자를 하나의 메세지로 만듦
	char Message[1024];
	snprintf(Message, sizeof(Message), "Numbers&Operation: %d, %c, %d", randNum1, operationChar, randNum2);

	// 서버로 메세지 전송
	int SendSize = send(ClientSocket, Message, (int)strlen(Message), 0);
	if (SendSize <= 0)
	{
		printf("send error or disconnected %d\n", GetLastError());
		exit(-1);
	}

	// 서버로부터 응답 받기
	char Buffer[1024] = { 0, };
	int RecvSize = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
	if (RecvSize <= 0)
	{
		printf("recv error or disconnected %d\n", GetLastError());
		exit(-1);
	}

	printf("%s from server", Buffer);

	closesocket(ClientSocket);

	WSACleanup();


	return 0;
}