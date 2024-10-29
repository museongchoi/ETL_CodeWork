#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == SOCKET_ERROR)
	{
		printf("socket error %d\n", GetLastError());
		exit(-1);
	}

	SOCKADDR_IN ListenSock;
	memset(&ListenSock, 0, sizeof(ListenSock));
	ListenSock.sin_family = AF_INET;
	ListenSock.sin_addr.s_addr = INADDR_ANY;
	ListenSock.sin_port = htons(30000);

	int Result = bind(ListenSocket, (SOCKADDR*)&ListenSock, sizeof(ListenSock));
	if (Result == SOCKET_ERROR)
	{
		printf("bind error %d\n", GetLastError());
		exit(-1);
	}

	listen(ListenSocket, 5);

	while (true)
	{
		SOCKADDR_IN ClientSock;
		memset(&ClientSock, 0, sizeof(ClientSock));
		int ClientSockSize = sizeof(ClientSock);
		SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSock, &ClientSockSize);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept error %d\n", GetLastError());
			exit(-1);
		}

		char Buffer[1024] = { 0, };
		int RecvSize = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
		if (RecvSize <= 0)
		{
			printf("recv error or disconnected %d\n", GetLastError());
			exit(-1);
		}

		printf("%s from client\n", Buffer);

		// 두개의 숫자와 연산자를 문자열에서 분리하여 변환
		char* token = strtok(Buffer, ", ");
		if (token == NULL)
		{
			printf("Invalid message format : Num1\n");
			exit(-1);
		}
		int num1 = atoi(token);

		token = strtok(NULL, ", ");
		if (token == NULL)
		{
			printf("Invalid message format : Op\n");
			exit(-1);

		}
		char operationChar = atoi(token);

		token = strtok(NULL, ", ");
		if (token == NULL)
		{
			printf("Invalid message format : Num2\n");
			exit(-1);
		}
		int num2 = atoi(token);

		// 연산 수행
		int result = 0;
		switch (operationChar)
		{
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			if (num2 != 0)
				result = num1 / num2;
			else
				result = 0; // Division by zero 처리
			break;
		default:
			printf("Invalid operation character\n");
			exit(-1);
		}

		// 결과를 문자열로 변환
		char ResultMessage[1024];
		snprintf(ResultMessage, sizeof(ResultMessage), "%d %c %d = %d", num1, operationChar, num2, result);

		int SendSize = send(ClientSocket, ResultMessage, (int)strlen(ResultMessage), 0);
		if (SendSize <= 0)
		{
			printf("send error or disconnected %d\n", GetLastError());
			exit(-1);
		}
		closesocket(ClientSocket);

	}
	
	//closesocket(ClientSocket);
	closesocket(ListenSocket);

	WSACleanup();

	return 0;
}