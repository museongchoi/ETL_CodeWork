#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define FD_SETSIZE      100


#include <stdio.h>
#include <WinSock2.h>
#include "Packet.h"
#include "Session.h"

using namespace std;

#pragma comment(lib, "ws2_32")

Session MySession;


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
						MySession.Insert(ClientSocket, SessionInfo());

						char* IP = inet_ntoa(ClientSock.sin_addr);

						printf("%s connected.\n", IP);

						//PostLogin, 유저가 접속하면 인증
						Packet PostLoginPacket;
						PostLoginPacket.Code = (unsigned short)ECommand::PostLogin;
						PostLoginPacket.X = MySession.List[ClientSocket].X;
						PostLoginPacket.Y = MySession.List[ClientSocket].Y;
						PostLoginPacket.R = MySession.List[ClientSocket].R;
						PostLoginPacket.G = MySession.List[ClientSocket].G;
						PostLoginPacket.B = MySession.List[ClientSocket].B;
						PostLoginPacket.Id = ClientSocket;
						MakeNetworkOrder(PostLoginPacket);
						Length = htons(sizeof(PostLoginPacket));
						int SendSize = send(ClientSocket, (char*)&Length, sizeof(Length), 0);
						SendSize = send(ClientSocket, (char*)&PostLoginPacket, sizeof(PostLoginPacket), 0);


						//send -> All Client Spawn
						Packet SpawnPacket;
						SpawnPacket.Code = (unsigned short)ECommand::Spawn;
						SpawnPacket.X = MySession.List[ClientSocket].X;
						SpawnPacket.Y = MySession.List[ClientSocket].Y;
						SpawnPacket.R = MySession.List[ClientSocket].R;
						SpawnPacket.G = MySession.List[ClientSocket].G;
						SpawnPacket.B = MySession.List[ClientSocket].B;
						SpawnPacket.Id = ClientSocket;
						MakeNetworkOrder(SpawnPacket);

						for (auto RecvSession : MySession.List)
						{
							Length = htons(sizeof(SpawnPacket));

							int SendSize = send(RecvSession.first, (char*)&Length, sizeof(Length), 0);
							SendSize = send(RecvSession.first, (char*)&SpawnPacket, sizeof(SpawnPacket), 0);
						}

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

							SOCKET DisconnectedSocket = ReadSocketList.fd_array[i];

							//disconnect
							closesocket(DisconnectedSocket);
							FD_CLR(DisconnectedSocket, &ReadSocketList);

							// MySession 에서 클라이언트 세션 제거
							MySession.Remove(DisconnectedSocket);

							// 모든 클라이언트에게 해당 클라이언트가 종료되었음을 알림
							Packet DestroyPacket;
							DestroyPacket.Code = (unsigned short)ECommand::Destroy;
							DestroyPacket.Id = DisconnectedSocket;
							MakeNetworkOrder(DestroyPacket);

							Length = htons(sizeof(DestroyPacket));
							for (int j = 0; j < (int)ReadSocketList.fd_count; j++)
							{
								if (ReadSocketList.fd_array[j] != ListenSocket && ReadSocketList.fd_array[j] != DisconnectedSocket)
								{
									int SendSize = send(ReadSocketList.fd_array[j], (char*)&Length, sizeof(Length), 0);
									SendSize = send(ReadSocketList.fd_array[j], (char*)&DestroyPacket, sizeof(DestroyPacket), 0);
								}
							}

							// 화면 초기화 후 갱신
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
						else
						{
							//get client ip
							SOCKADDR_IN ClientSock;
							memset(&ClientSock, 0, sizeof(ClientSock));
							int ClientSockSize = sizeof(ClientSock);
							getpeername(ReadSocketList.fd_array[i], (SOCKADDR*)&ClientSock, &ClientSockSize);
							char* IP = inet_ntoa(ClientSock.sin_addr);

							//parsing
							MakeHostOrder(Data);

							SessionInfo FindSession = MySession.List[Data.Id];

							//process
							switch ((ECommand)(Data.Code))
							{
							case ECommand::Up:
								FindSession.Y--;
								break;
							case ECommand::Down:
								FindSession.Y++;
								break;
							case ECommand::Left:
								FindSession.X--;
								break;
							case ECommand::Right:
								FindSession.X++;
								break;
							}

							MySession.List[Data.Id] = FindSession;

							//render
							system("cls");

							for (auto CurrentSession : MySession.List)
							{
								COORD Pos;
								Pos.X = CurrentSession.second.X;
								Pos.Y = CurrentSession.second.Y;
								SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
								printf("*");
							}

							Packet SetPacket;


							//send Set Packet 
							SetPacket.X = FindSession.X;
							SetPacket.Y = FindSession.Y;
							SetPacket.R = FindSession.R;
							SetPacket.G = FindSession.G;
							SetPacket.B = FindSession.B;
							SetPacket.Id = Data.Id;
							SetPacket.Code = (u_short)(ECommand::Set);

							MakeNetworkOrder(SetPacket);

							Length = htons(sizeof(Data));

							for (int j = 0; j < (int)ReadSocketList.fd_count; ++j)
							{
								if (ReadSocketList.fd_array[j] != ListenSocket)
								{
									int SendSize = send(ReadSocketList.fd_array[j], (char*)&Length, sizeof(Length), 0);
									SendSize = send(ReadSocketList.fd_array[j], (char*)&SetPacket, sizeof(SetPacket), 0);
								}
							}
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