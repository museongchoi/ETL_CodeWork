// ���� �� �ڵ�
#ifdef _DEBUG
#pragma comment(lib, "./mysql-connector/lib64/debug/vs14/mysqlcppconn.lib")
#else
#pragma comment(lib, "./mysql-connector/lib64/vs14/mysqlcppconn.lib")
#endif

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "jdbc/mysql_driver.h"
#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/prepared_statement.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 54000
#define BUFFER_SIZE 4096

using namespace std;

void handle_client(SOCKET client_socket);

int main() {
    // WinSock �ʱ�ȭ
    WSADATA wsData;
    int wsInit = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (wsInit != 0) {
        cerr << "WinSock�� �ʱ�ȭ�� �� �����ϴ�! �����մϴ�." << endl;
        return -1;
    }

    // ���� ����
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        cerr << "������ ������ �� �����ϴ�! �����մϴ�." << endl;
        WSACleanup();
        return -1;
    }

    int optval = 1;
    setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

    // ������ IP/��Ʈ�� ���ε�
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(SERVER_PORT);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;


    // ������ ���� ��� ���·� ����
    listen(listening, SOMAXCONN);

    cout << "������ ��Ʈ " << SERVER_PORT << "���� ���� ��� ���Դϴ�..." << endl;

    // ������ ���� ������ ���� ����
    while (true) {
        sockaddr_in client;
        int clientSize = sizeof(client);

        SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            int error_code = WSAGetLastError();
            cerr << "accept()���� ������ �߻��߽��ϴ�. ���� �ڵ�: " << error_code << " �����մϴ�." << endl;
            closesocket(listening);
            WSACleanup();
            return -1;
        }

        // Ŭ���̾�Ʈ�� ó���� ������ ����
        thread clientThread(handle_client, clientSocket);
        clientThread.detach();
    }

    // ���� ��� ���� �ݱ�
    closesocket(listening);

    // WinSock ����
    WSACleanup();

    return 0;
}

void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    int bytesReceived;

    try {
        sql::Driver* driver = get_driver_instance();
        sql::Connection* connection = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
        connection->setSchema("usertest");

        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "recv()���� ������ �߻��߽��ϴ�." << endl;
                break;
            }

            if (bytesReceived == 0) {
                cout << "Ŭ���̾�Ʈ�� ������ �������ϴ�." << endl;
                break;
            }

            string received(buffer, 0, bytesReceived);
            if (received.find("REGISTER") == 0) {
                // ����� ���� �Ľ�
                string user_id, password, birthday;
                cout << "User ID: ";
                cin >> user_id;
                cout << "Password: ";
                cin >> password;
                cout << "Birthday (YYYY-MM-DD): ";
                cin >> birthday;

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "INSERT INTO users (user_id, user_password, birthday, created_at, is_del) VALUES (?, ?, ?, NOW(), 0)"
                );
                pstmt->setString(1, user_id);
                pstmt->setString(2, password);
                pstmt->setString(3, birthday);

                try {
                    pstmt->executeUpdate();
                    send(client_socket, "REGISTER SUCCESS", 15, 0);
                }
                catch (sql::SQLException e) {
                    send(client_socket, "REGISTER FAILED", 14, 0);
                }

                delete pstmt;
            }
            else if (received.find("LOGIN") == 0) {
                // ����� ���� �Ľ�
                string user_id, password;
                cout << "User ID: ";
                cin >> user_id;
                cout << "Password: ";
                cin >> password;

                sql::PreparedStatement* pstmt = connection->prepareStatement(
                    "SELECT * FROM users WHERE user_id = ? AND user_password = ? AND is_del = 0"
                );
                pstmt->setString(1, user_id);
                pstmt->setString(2, password);

                sql::ResultSet* resultSet = pstmt->executeQuery();

                if (resultSet->next()) {
                    send(client_socket, "LOGIN SUCCESS", 13, 0);
                }
                else {
                    send(client_socket, "LOGIN FAILED", 12, 0);
                }

                delete pstmt;
                delete resultSet;
            }
        }

        delete connection;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL ����: " << e.what() << endl;
    }

    closesocket(client_socket);
}