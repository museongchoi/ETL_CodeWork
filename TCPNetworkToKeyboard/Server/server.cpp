#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define FD_SETSIZE      100


#include <stdio.h>
#include <WinSock2.h>
using namespace std;

#pragma comment(lib, "ws2_32")


enum class ECommand
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
	Set = 4,
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
	int X = 5;
	int Y = 5;

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ListenSock;
	memset(&ListenSock, 0, sizeof(ListenSock));
	ListenSock.sin_family = PF_INET;
	ListenSock.sin_addr.s_addr = INADDR_ANY;
	ListenSock.sin_port = htons(30000);

	int Result = bind(ListenSocket, (SOCKADDR*)&ListenSock, sizeof(ListenSock));

	listen(ListenSocket, 5);
	struct timeval TimeOut;
	TimeOut.tv_sec = 1;
	TimeOut.tv_usec = 0;

	Packet Data;

	fd_set ReadSocketList;
	fd_set CopyReadSocketList;

	FD_ZERO(&ReadSocketList);
	FD_SET(ListenSocket, &ReadSocketList);

	while (true)
	{
		CopyReadSocketList = ReadSocketList;

		int ChangeFDCount = select(0, &CopyReadSocketList, 0, 0, &TimeOut);
		if (ChangeFDCount == 0)
		{
			//printf("nothing\n");
			//No chanage
			//other process
			//re polling
			continue;
		}
		else if (ChangeFDCount < 0)
		{
			//error
			printf("error %d", GetLastError());
			exit(-1);
		}
		else //(ChangeFDCount > 0)
		{
			for (int i = 0; i < (int)ReadSocketList.fd_count; ++i)
			{
				if (FD_ISSET(ReadSocketList.fd_array[i], &CopyReadSocketList))
				{
					if (ReadSocketList.fd_array[i] == ListenSocket)
					{
						//accept
						SOCKADDR_IN ClientSock;
						memset(&ClientSock, 0, sizeof(ClientSock));
						int ClientSockSize = sizeof(ClientSock);
						SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSock, &ClientSockSize);
						FD_SET(ClientSocket, &ReadSocketList);

						char* IP = inet_ntoa(ClientSock.sin_addr);

						printf("%s connected.\n", IP);
					}
					else
					{
						//init
						memset(&Data, 0, sizeof(Data));

						//read
						//[][] [][][][][][]
						u_short Length = 0;
						int RecvBytes = recv(ReadSocketList.fd_array[i], (char*)&Length, sizeof(Length), MSG_WAITALL);

						Length = ntohs(Length);
						RecvBytes = recv(ReadSocketList.fd_array[i], (char*)&Data, Length, MSG_WAITALL);

						if (RecvBytes <= 0)
						{
							SOCKADDR_IN ClientSock;
							memset(&ClientSock, 0, sizeof(ClientSock));
							int ClientSockSize = sizeof(ClientSock);

							getpeername(ReadSocketList.fd_array[i], (SOCKADDR*)&ClientSock, &ClientSockSize);
							char* IP = inet_ntoa(ClientSock.sin_addr);

							printf("%s disconnected.\n", IP);

							//disconnect
							closesocket(ReadSocketList.fd_array[i]);
							FD_CLR(ReadSocketList.fd_array[i], &ReadSocketList);

						}
						else
						{
							//get client ip
							SOCKADDR_IN ClientSock;
							memset(&ClientSock, 0, sizeof(ClientSock));
							int ClientSockSize = sizeof(ClientSock);
							getpeername(ReadSocketList.fd_array[i], (SOCKADDR*)&ClientSock, &ClientSockSize);
							char* IP = inet_ntoa(ClientSock.sin_addr);

							//parsing
							Data.Code = ntohs(Data.Code);

							//process
							switch ((ECommand)(Data.Code))
							{
							case ECommand::Up:
								Y--;
								break;
							case ECommand::Down:
								Y++;
								break;
							case ECommand::Left:
								X--;
								break;
							case ECommand::Right:
								X++;
								break;
							}

							//render
							system("cls");

							COORD Pos;
							Pos.X = X;
							Pos.Y = Y;
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
							printf("*");

							//replicate
							Data.Code = (u_short)ECommand::Set;
							Data.X = X;
							Data.Y = Y;

							Data.Code = htons(Data.Code);
							Data.X = htons(X);
							Data.Y = htons(Y);

							Length = htons(sizeof(Data));

							int SendSize = send(ReadSocketList.fd_array[i], (char*)&Length, sizeof(Length), 0);
							SendSize = send(ReadSocketList.fd_array[i], (char*)&Data, sizeof(Data), 0);
						}
					}
				}
			}
			//network process

		}
	}


	closesocket(ListenSocket);


	WSACleanup();


	return 0;
}