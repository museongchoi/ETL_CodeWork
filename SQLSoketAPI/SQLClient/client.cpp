// Ŭ���̾�Ʈ �� �ڵ�

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
    // WinSock �ʱ�ȭ
    WSADATA wsData;
    int wsInit = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (wsInit != 0) {
        cerr << "WinSock�� �ʱ�ȭ�� �� �����ϴ�! �����մϴ�." << endl;
        return -1;
    }

    // ���� ����
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "������ ������ �� �����ϴ�! �����մϴ�." << endl;
        WSACleanup();
        return -1;
    }

    // ������ ����
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server.sin_addr);

    int connResult = connect(sock, (sockaddr*)&server, sizeof(server));
    if (connResult == SOCKET_ERROR) {
        cerr << "������ ������ �� �����ϴ�! �����մϴ�." << endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // ����ڷκ��� ��� �Է�
    string command;
    char buffer[BUFFER_SIZE];

    while (true) {
        cout << "��ɾ �Է��ϼ��� (REGISTER/LOGIN/EXIT): ";
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

            // ������ ��� ����
            int sendResult = send(sock, command.c_str(), command.size() + 1, 0);
            if (sendResult != SOCKET_ERROR) {
                memset(buffer, 0, BUFFER_SIZE);
                int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);
                if (bytesReceived > 0) {
                    cout << "���� ����: " << string(buffer, 0, bytesReceived) << endl;
                }
            }
        }
        else {
            cout << "�߸��� ��ɾ��Դϴ�." << endl;
        }
    }

    // ���� �ݱ�
    closesocket(sock);
    WSACleanup();

    return 0;
}