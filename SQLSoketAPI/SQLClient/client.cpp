// 클라이언트 측 코드

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 54000  
#define BUFFER_SIZE 4096

using namespace std;

int main() {
    // WinSock 초기화
    WSADATA wsData;
    int wsInit = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (wsInit != 0) {
        cerr << "WinSock을 초기화할 수 없습니다! 종료합니다." << endl;
        return -1;
    }

    // 소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "소켓을 생성할 수 없습니다! 종료합니다." << endl;
        WSACleanup();
        return -1;
    }

    // 서버에 연결
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server.sin_addr);

    int connResult = connect(sock, (sockaddr*)&server, sizeof(server));
    if (connResult == SOCKET_ERROR) {
        cerr << "서버에 연결할 수 없습니다! 종료합니다." << endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // 사용자로부터 명령 입력
    string command;
    char buffer[BUFFER_SIZE];

    while (true) {
        cout << "명령어를 입력하세요 (REGISTER/LOGIN/EXIT): ";
        getline(cin, command);

        if (command == "EXIT") {
            break;
        }

        if (command == "REGISTER" || command == "LOGIN") {
            string user_id, password, birthday;
            cout << "User ID: ";
            getline(cin, user_id);
            cout << "Password: ";
            getline(cin, password);

            if (command == "REGISTER") {
                cout << "Birthday (YYYY-MM-DD): ";
                getline(cin, birthday);
                command += " " + user_id + " " + password + " " + birthday;
            }
            else {
                command += " " + user_id + " " + password;
            }

            // 서버로 명령 전송
            int sendResult = send(sock, command.c_str(), command.size() + 1, 0);
            if (sendResult != SOCKET_ERROR) {
                memset(buffer, 0, BUFFER_SIZE);
                int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);
                if (bytesReceived > 0) {
                    cout << "서버 응답: " << string(buffer, 0, bytesReceived) << endl;
                }
            }
        }
        else {
            cout << "잘못된 명령어입니다." << endl;
        }
    }

    // 소켓 닫기
    closesocket(sock);
    WSACleanup();

    return 0;
}