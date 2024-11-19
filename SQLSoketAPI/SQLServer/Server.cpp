// 서버 측 코드
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
    // WinSock 초기화
    WSADATA wsData;
    int wsInit = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (wsInit != 0) {
        cerr << "WinSock을 초기화할 수 없습니다! 종료합니다." << endl;
        return -1;
    }

    // 소켓 생성
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        cerr << "소켓을 생성할 수 없습니다! 종료합니다." << endl;
        WSACleanup();
        return -1;
    }

    int optval = 1;
    setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

    // 소켓을 IP/포트에 바인딩
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(SERVER_PORT);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;


    // 소켓을 수신 대기 상태로 설정
    listen(listening, SOMAXCONN);

    cout << "서버가 포트 " << SERVER_PORT << "에서 수신 대기 중입니다..." << endl;

    // 루프를 돌며 들어오는 연결 수락
    while (true) {
        sockaddr_in client;
        int clientSize = sizeof(client);

        SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            int error_code = WSAGetLastError();
            cerr << "accept()에서 오류가 발생했습니다. 오류 코드: " << error_code << " 종료합니다." << endl;
            closesocket(listening);
            WSACleanup();
            return -1;
        }

        // 클라이언트를 처리할 스레드 시작
        thread clientThread(handle_client, clientSocket);
        clientThread.detach();
    }

    // 수신 대기 소켓 닫기
    closesocket(listening);

    // WinSock 정리
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
                cerr << "recv()에서 오류가 발생했습니다." << endl;
                break;
            }

            if (bytesReceived == 0) {
                cout << "클라이언트가 연결을 끊었습니다." << endl;
                break;
            }

            string received(buffer, 0, bytesReceived);
            if (received.find("REGISTER") == 0) {
                // 사용자 정보 파싱
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
                // 사용자 정보 파싱
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
        cerr << "SQL 오류: " << e.what() << endl;
    }

    closesocket(client_socket);
}