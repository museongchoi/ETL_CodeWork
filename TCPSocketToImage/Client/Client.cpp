#define  _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
	// fopen : ���� ����
	FILE* InputFile = fopen("./pororo.png", "rb");

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in ServerSockAddr;
	ZeroMemory(&ServerSockAddr, 0);
	ServerSockAddr.sin_family = PF_INET;
	//ListenSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(PF_INET, "127.0.0.1", (void*)&(ServerSockAddr.sin_addr.s_addr));
	ServerSockAddr.sin_port = htons(30000);

	connect(ServerSocket, (struct sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	// Buffer �� ������(����)�� �ѹ��� �д� ��Ŷ�� ����(����)
	char Buffer[4096] = { 0, };
	int SendBytes = 0;
	size_t ReadSize = 0;

	// size �� 0�̸� ���� ���� ���̴�.
	do
	{
		ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), InputFile);
		// ���� �� ��ŭ ���ִ� ������ Buffer�� size�� �� �����ؾ��Ѵ�.
		//size_t WriteSize = fwrite(Buffer, sizeof(char), sizeof(Buffer), InputFile);
		SendBytes = send(ServerSocket, Buffer, (int)ReadSize, 0);
	} while (ReadSize > 0);
	// while ���� ���ٸ� ��ü ���� �뷮 �� �ѹ��� ���� ���̱� ������ ���纻�� ������ �ʴ´�.
	// ��, �ش� �̹��� ���Ͽ� �� �뷮�� 4�Ⱑ�̰� Buffer �� ���̰� 4090kb�� �ѹ� ���� ��.
	// �׷��Ƿ� while ���� ����Ͽ� �ش� �̹��� ��ü�� �д� ���̴�.

	// fclose : ���� �ݱ�
	fclose(InputFile);

	closesocket(ServerSocket);

	WSACleanup();

	return 0;


}