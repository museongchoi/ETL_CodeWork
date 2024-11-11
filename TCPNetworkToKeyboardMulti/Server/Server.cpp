#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define FD_SETSIZE      100

#include <stdio.h>
#include <WinSock2.h>
#include <thread>
#include <vector>
#include <mutex>

#pragma comment(lib, "ws2_32")

using namespace std;

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

// 플레이어 위치 정보
int X = 5;
int Y = 5;

// 멀티스레드 동기화를 위한 뮤텍스
typedef std::lock_guard<std::mutex> LockGuard;
std::mutex playerMutex;
vector<SOCKET> clientSockets;
std::mutex clientSocketsMutex;

void BroadcastPosition()
{
    LockGuard lock(clientSocketsMutex);
    Packet Data;
    Data.Code = (u_short)ECommand::Set;
    Data.X = X;
    Data.Y = Y;

    Data.Code = htons(Data.Code);
    Data.X = htons(X);
    Data.Y = htons(Y);

    unsigned short Length = htons(sizeof(Data));

    for (SOCKET clientSocket : clientSockets)
    {
        send(clientSocket, (char*)&Length, sizeof(Length), 0);
        send(clientSocket, (char*)&Data, sizeof(Data), 0);
    }
}

void HandleClient(SOCKET ClientSocket)
{
    Packet Data;
    while (true)
    {
        // init
        memset(&Data, 0, sizeof(Data));

        // read
        u_short Length = 0;
        int RecvBytes = recv(ClientSocket, (char*)&Length, sizeof(Length), MSG_WAITALL);

        if (RecvBytes <= 0)
        {
            printf("Client disconnected\n");
            closesocket(ClientSocket);
            {
                LockGuard lock(clientSocketsMutex);
                clientSockets.erase(remove(clientSockets.begin(), clientSockets.end(), ClientSocket), clientSockets.end());
            }
            return;
        }

        Length = ntohs(Length);
        RecvBytes = recv(ClientSocket, (char*)&Data, Length, MSG_WAITALL);

        if (RecvBytes <= 0)
        {
            printf("Client disconnected\n");
            closesocket(ClientSocket);
            {
                LockGuard lock(clientSocketsMutex);
                clientSockets.erase(remove(clientSockets.begin(), clientSockets.end(), ClientSocket), clientSockets.end());
            }
            return;
        }

        // Parsing
        Data.Code = ntohs(Data.Code);

        // Process
        LockGuard lock(playerMutex);
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

        // Render
        system("cls");
        COORD Pos;
        Pos.X = X;
        Pos.Y = Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
        printf("*");

        // Broadcast updated position to all clients
        BroadcastPosition();
    }
}

int main()
{
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN ListenSock;
    memset(&ListenSock, 0, sizeof(ListenSock));
    ListenSock.sin_family = PF_INET;
    ListenSock.sin_addr.s_addr = INADDR_ANY;
    ListenSock.sin_port = htons(30000);

    bind(ListenSocket, (SOCKADDR*)&ListenSock, sizeof(ListenSock));
    listen(ListenSocket, 5);

    printf("Server is listening on port 30000\n");

    while (true)
    {
        SOCKADDR_IN ClientSock;
        memset(&ClientSock, 0, sizeof(ClientSock));
        int ClientSockSize = sizeof(ClientSock);
        SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSock, &ClientSockSize);

        if (ClientSocket != INVALID_SOCKET)
        {
            printf("Client connected: %s\n", inet_ntoa(ClientSock.sin_addr));
            {
                LockGuard lock(clientSocketsMutex);
                clientSockets.push_back(ClientSocket);
            }
            thread clientThread(HandleClient, ClientSocket);
            clientThread.detach();
        }
    }

    closesocket(ListenSocket);
    WSACleanup();
    return 0;
}