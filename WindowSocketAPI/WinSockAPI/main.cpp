#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hostent* hostinfo = gethostbyname("test.com");
	//getaddrinfo()

	printf("hostname : %s\n", hostinfo->h_name);

	//for (int i = 0; hostinfo->h_aliases[i] != nullptr; ++i)
	//{
	//	printf("host alias : %s\n", hostinfo->h_aliases[i]);
	//}

	//127.0.0.1 -> string -> in_addr
	//google.com -> in_addr

	//[][][][]
	//[][][][] [][][][] [][][][] [][][][]
//	for (int i = 0; hostinfo->h_addr_list[i] != nullptr; ++i)
	for (int i = 0; hostinfo->h_addr_list[i]; ++i)
	{
		IN_ADDR Addr = *(IN_ADDR*)(hostinfo->h_addr_list[i]);
		char ClientIP[30] = { 0, };

		if (inet_ntop(AF_INET, &Addr, ClientIP, sizeof(ClientIP)) != NULL)
		{
			printf("host ip : %s\n", ClientIP);
		}
		printf("host ip : %s\n", inet_ntoa(Addr));
	}


	WSACleanup();

	return 0;
}