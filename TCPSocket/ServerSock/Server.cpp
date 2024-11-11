#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32")

int main()
{
	//[][] [][]
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

		printf("%s\n", Buffer);

		string Message = Buffer;
		size_t Position = Message.find('+');
		if (Position == string::npos)
		{
			Position = Message.find('-');
		}

		if (Position == string::npos)
		{
			Position = Message.find('*');
		}

		if (Position == string::npos)
		{
			Position = Message.find('/');
		}

		if (Position == string::npos)
		{
			Position = Message.find('%');
		}

		if (Position == string::npos)
		{
			continue;
		}



		//100+20
		//1*2000
		int FirstNumber = 0;
		int SecondNumber = 0;
		int Result = 0;

		string FirstNumberString;
		string SecondNumberString;
		FirstNumberString = Message.substr(0, Position);
		SecondNumberString = Message.substr(Position + 1, Message.length() - Position);

		FirstNumber = atoi(FirstNumberString.c_str());
		SecondNumber = atoi(SecondNumberString.c_str());

		switch (Message[Position])
		{
		case '+':
			Result = FirstNumber + SecondNumber;
			break;
		case '-':
			Result = FirstNumber - SecondNumber;
			break;
		case '*':
			Result = FirstNumber * SecondNumber;
			break;
		case '/':
			Result = FirstNumber / SecondNumber;
			break;
		case '%':
			Result = FirstNumber % SecondNumber;
			break;
		}

		char ResultMessage[1024] = { 0, };
		sprintf(ResultMessage, "%d", Result);

		int SendSize = send(ClientSocket, ResultMessage, (int)strlen(ResultMessage), 0);
		if (SendSize <= 0)
		{
			printf("send error or disconnected %d\n", GetLastError());
			exit(-1);
		}

		closesocket(ClientSocket);
	}
	closesocket(ListenSocket);


	WSACleanup();


	return 0;
}