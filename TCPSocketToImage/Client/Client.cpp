#define  _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
	// fopen : 파일 열기
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

	// Buffer 의 사이즈(길이)는 한번에 읽는 패킷의 단위(길이)
	char Buffer[4096] = { 0, };
	int SendBytes = 0;
	size_t ReadSize = 0;

	// size 가 0이면 읽지 못한 것이다.
	do
	{
		ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), InputFile);
		// 읽은 것 만큼 써주는 것으로 Buffer의 size를 잘 설정해야한다.
		//size_t WriteSize = fwrite(Buffer, sizeof(char), sizeof(Buffer), InputFile);
		SendBytes = send(ServerSocket, Buffer, (int)ReadSize, 0);
	} while (ReadSize > 0);
	// while 문이 없다면 전체 파일 용량 중 한번만 읽은 것이기 때문에 복사본이 열리지 않는다.
	// 즉, 해당 이미지 파일에 총 용량이 4기가이고 Buffer 의 길이가 4090kb씩 한번 읽은 것.
	// 그러므로 while 문을 사용하여 해당 이미지 전체를 읽는 것이다.

	// fclose : 파일 닫기
	fclose(InputFile);

	closesocket(ServerSocket);

	WSACleanup();

	return 0;


}