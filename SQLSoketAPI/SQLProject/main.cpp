#ifdef _DEBUG
#pragma comment(lib, "./mysql-connector/lib64/debug/vs14/mysqlcppconn.lib")
#else
#pragma comment(lib, "./mysql-connector/lib64/vs14/mysqlcppconn.lib")
#endif

#include <string>
#include <iostream>
#include <exception> // try&catch ����ó���� �߰� �������
#include <vector>
#include <Windows.h>

#include "jdbc/mysql_driver.h" // os �� hw �� ��� api
#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/exception.h"
#include <regex> // �Է°� ��ȿ�� �˻翡 ���

using namespace std;

std::string Utf8ToMultiByte(std::string utf8_str);
std::string MultiByteToUtf8(std::string multibyte_str);

class customexeception : exception
{
public:
	customexeception(string what)
	{
		message = what;
	}

	string message;
};

bool isValidInput(const string& user_id, const string& password, const string& birthday) {
	// ����� ID�� �ּ� 4�� �̻�
	if (user_id.empty() || user_id.length() < 4) {
		cout << "User ID must be at least 4 characters long." << endl;
		return false;
	}

	// ��й�ȣ�� �ּ� 6�� �̻�
	if (password.empty() || password.length() < 6) {
		cout << "Password must be at least 6 characters long." << endl;
		return false;
	}

	// ������ YYYY-MM-DD �����̾�� ��
	regex date_format("\\d{4}-\\d{2}-\\d{2}");
	if (!regex_match(birthday, date_format)) {
		cout << "Birthday must be in YYYY-MM-DD format." << endl;
		return false;
	}

	return true;
}

int main()
{
	//try
	//{
	//	//string s;
	//	//s.resize(-1);

	//	cout << 1 << endl;
	//	throw exception("�׽�Ʈ");
	//	cout << 2 << endl;

	//	cout << 1 << endl;
	//	throw customexception("�׽�Ʈ");
	//	cout << 2 << endl;

	//	vector<int> a;

	//	a.resize(-1);

	//}
	//catch (customexception& e)
	//{
	//	cout << e.message << endl;
	//}
	//catch(exception& e)
	//{
	//	cout << e.what() << endl;
	//}

	try {
		sql::Driver* driver = nullptr;
		sql::Connection* connection = nullptr;
		sql::Statement* statement = nullptr;
		sql::ResultSet* resultSet;
		sql::PreparedStatement* pstmt = nullptr;


		driver = get_driver_instance();

		connection = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
		connection->setSchema("usertest"); //use

		string user_id, password, birthday;
		int is_del = 0;

		while (true) {
			cout << "Enter User ID: ";
			cin >> user_id;

			cout << "Enter Password: ";
			cin >> password;

			cout << "Enter Birthday (YYYY-MM-DD): ";
			cin >> birthday;

			if (isValidInput(user_id, password, birthday)) {
				break; // ��ȿ�� �Է��̸� ���� ����
			}
			cout << "Invalid input. Please try again.\n" << endl;
		}

		// ������ ����
		pstmt = connection->prepareStatement(
			"INSERT INTO users (user_id, user_password, birthday, created_at, is_del) VALUES (?, ?, ?, NOW(), ?)"
		);
		pstmt->setString(1, user_id);
		pstmt->setString(2, password);
		pstmt->setString(3, birthday);
		pstmt->setInt(4, is_del);

		int rowsAffected = pstmt->executeUpdate();

		if (rowsAffected > 0) {
			cout << "Data successfully inserted!" << endl;
		}
		else {
			cout << "Failed to insert data." << endl;
		}

		delete pstmt;
		pstmt = nullptr;

		

		statement = connection->createStatement();
		resultSet = statement->executeQuery("select * from users;");


		if (!resultSet->next()) {
			cout << "No data found in the result set." << endl;
		}
		else {
			while (resultSet->next()) {
				cout << "User No: " << resultSet->getInt("userno") << endl;
				cout << "UserID: " << resultSet->getString("user_id") << endl;
				cout << "Userbirthday: " << resultSet->getString("birthday") << endl;
				cout << "User No: " << resultSet->getInt("is_del") << endl;
			};

			cout << "���ڵ� ��" << endl;
			cout << endl;


			resultSet = statement->executeQuery("select * from users;");

			while (resultSet->next())
			{
				for (int i = 1; i <= 6; i++)
				{
					cout << Utf8ToMultiByte(resultSet->getString(i)) << " : ";
				}
				cout << endl;
			}

		}

		delete resultSet;
		resultSet = nullptr;
		delete statement;
		statement = nullptr;
		delete connection;
		connection = nullptr;
		driver = nullptr;

	}
	catch (sql::SQLException& e) {
		cout << "Error :" << e.what() << endl;
		cout << "MySQL ErrorCode :" << e.getErrorCode() << endl;
		cout << "SQLState :" << e.getSQLState() << endl;
	}
	return 0;
}

/*
* @brief ������ ����ϴ� utf-8 ���ڵ��� window���� ����ϴ� ANSI ���ڵ����� ���� �մϴ�.
*/
std::string Utf8ToMultiByte(std::string utf8_str)
{
	std::string resultString;
	char* pszIn = new char[utf8_str.length() + 1];
	strncpy_s(pszIn, utf8_str.length() + 1, utf8_str.c_str(), utf8_str.length());

	int nLenOfUni = 0, nLenOfANSI = 0;
	wchar_t* uni_wchar = NULL;
	char* pszOut = NULL;

	// 1. utf8 Length
	if ((nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
		return 0;

	uni_wchar = new wchar_t[nLenOfUni + 1];
	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

	// 2. utf8 --> unicode
	nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

	// 3. ANSI(multibyte) Length
	if ((nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
	{
		delete[] uni_wchar;
		return 0;
	}

	pszOut = new char[nLenOfANSI + 1];
	memset(pszOut, 0x00, sizeof(char) * (nLenOfANSI + 1));

	// 4. unicode --> ANSI(multibyte)
	nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, pszOut, nLenOfANSI, NULL, NULL);
	pszOut[nLenOfANSI] = 0;
	resultString = pszOut;

	delete[] uni_wchar;
	delete[] pszOut;

	return resultString;
}

/*
* @brief window���� ����ϴ� ANSI ���ڵ��� ������ ����ϴ� utf-8 ���ڵ� ���ڵ����� ���� �մϴ�.
*/
std::string MultiByteToUtf8(std::string multibyte_str)
{
	char* pszIn = new char[multibyte_str.length() + 1];
	strncpy_s(pszIn, multibyte_str.length() + 1, multibyte_str.c_str(), multibyte_str.length());

	std::string resultString;

	int nLenOfUni = 0, nLenOfUTF = 0;
	wchar_t* uni_wchar = NULL;
	char* pszOut = NULL;

	// 1. ANSI(multibyte) Length
	if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
		return 0;

	uni_wchar = new wchar_t[nLenOfUni + 1];
	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

	// 2. ANSI(multibyte) ---> unicode
	nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

	// 3. utf8 Length
	if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
	{
		delete[] uni_wchar;
		return 0;
	}

	pszOut = new char[nLenOfUTF + 1];
	memset(pszOut, 0, sizeof(char) * (nLenOfUTF + 1));

	// 4. unicode ---> utf8
	nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
	pszOut[nLenOfUTF] = 0;
	resultString = pszOut;

	delete[] uni_wchar;
	delete[] pszOut;

	return resultString;
}

//ù��° �ڵ�
//#ifdef _DEBUG
//#pragma comment(lib, "./mysql-connector/lib64/debug/vs14/mysqlcppconn.lib")
//#else
//#pragma comment(lib, "./mysql-connector/lib64/vs14/mysqlcppconn.lib")
//#endif
//
//
//#include <string>
//#include <iostream>
//#include <exception>
//#include <vector>
//
//#include "jdbc/mysql_driver.h"   
//#include "jdbc/mysql_connection.h"
//#include "jdbc/cppconn/statement.h"
//#include "jdbc/cppconn/resultset.h"
//#include "jdbc/cppconn/exception.h"
//
//using namespace std;
//
//class customexeception : exception
//{
//public:
//	customexeception(string what)
//	{
//		message = what;
//	}
//
//	string message;
//};
//
//int main()
//{
//	//try
//	//{
//	//	char* p = nullptr;
//
//	//	cout << 1 << endl;
//	//	//throw customexeception("�̰� �׽�Ʈ ����");
//	//	cout << 2 << endl;
//	//	
//	//	vector<int> a;
//
//	//	a.resize(-1);
//
//	//}
//	//catch (customexeception& e)
//	//{
//	//	cout << e.message << endl;
//	//}
//	//catch ( exception& e)
//	//{
//	//	cout << e.what() << endl;
//	//}
//
//
//	try
//	{
//		sql::Driver* driver = nullptr;
//		sql::Connection* connection = nullptr;
//		sql::Statement* statement = nullptr;
//		sql::ResultSet* resultSet = nullptr;
//
//		driver = get_driver_instance();
//
//		connection = driver->connect("tcp://127.0.0.1", "root", "qweasd123");
//
//		connection->setSchema("member"); //use
//
//		statement = connection->createStatement();
//		resultSet = statement->executeQuery("SELECT * FROM member.user limit 0, 1000;");
//
//		std::cout << resultSet->getInt("no") << std::endl;
//
//		delete resultSet;
//		resultSet = nullptr;
//		delete statement;
//		statement = nullptr;
//		delete connection;
//		connection = nullptr;
//		driver = nullptr;
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "FILE :" << __FILE__ << endl;
//		cout << "LINE :" << __LINE__ << endl;
//		cout << "Error :" << e.what() << endl;
//		cout << "MySQL ErrorCode :" << e.getErrorCode() << endl;
//		cout << "SQLState :" << e.getSQLState() << endl;
//	}
//
//
//	return 0;
//}


// �ι�° �ڵ�
//#ifdef _DEBUG
//#pragma comment(lib, "./mysql-connector/lib64/debug/vs14/mysqlcppconn.lib")
//#else
//#pragma comment(lib, "./mysql-connector/lib64/vs14/mysqlcppconn.lib")
//#endif
//
//
//#include <string>
//#include <iostream>
//#include <exception>
//#include <vector>
//#include <Windows.h>
//
//#include "jdbc/mysql_driver.h"   
//#include "jdbc/mysql_connection.h"
//#include "jdbc/cppconn/statement.h"
//#include "jdbc/cppconn/resultset.h"
//#include "jdbc/cppconn/exception.h"
//
//using namespace std;
//
//std::string Utf8ToMultiByte(std::string utf8_str);
//std::string MultiByteToUtf8(std::string multibyte_str);
//
//class customexeception : exception
//{
//public:
//	customexeception(string what)
//	{
//		message = what;
//	}
//
//	string message;
//};
//
//int main()
//{
//	//try
//	//{
//	//	char* p = nullptr;
//
//	//	cout << 1 << endl;
//	//	//throw customexeception("�̰� �׽�Ʈ ����");
//	//	cout << 2 << endl;
//	//	
//	//	vector<int> a;
//
//	//	a.resize(-1);
//
//	//}
//	//catch (customexeception& e)
//	//{
//	//	cout << e.message << endl;
//	//}
//	//catch ( exception& e)
//	//{
//	//	cout << e.what() << endl;
//	//}
//
//
//	try
//	{
//		sql::Driver* driver = nullptr;
//		sql::Connection* connection = nullptr;
//		sql::Statement* statement = nullptr;
//		sql::ResultSet* resultSet;
//
//		driver = get_driver_instance();
//
//		connection = driver->connect("tcp://127.0.0.1", "root", "qweasd123");
//
//		connection->setSchema("member"); //use
//
//		statement = connection->createStatement();
//
//		resultSet = statement->executeQuery("SELECT * FROM user limit 0, 1000;");
//
//		while (resultSet->next())
//		{
//			cout << resultSet->getInt("no") << " : ";
//			cout << resultSet->getString("user_id") << " : ";
//			cout << resultSet->getString("user_password") << " : ";
//			cout << resultSet->getString("email") << " : ";
//			cout << resultSet->getString("created_at") << " : ";
//			cout << resultSet->getInt("is_del") << endl;
//		}
//
//		resultSet = statement->executeQuery("SELECT * FROM guestbook; ");
//
//		while (resultSet->next())
//		{
//			for (int i = 1; i <= 5; ++i)
//			{
//				cout << Utf8ToMultiByte(resultSet->getString(i)) << " : ";
//			}
//			cout << endl;
//		}
//
//		delete resultSet;
//		resultSet = nullptr;
//		delete statement;
//		statement = nullptr;
//		delete connection;
//		connection = nullptr;
//		driver = nullptr;
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "FILE :" << __FILE__ << endl;
//		cout << "LINE :" << __LINE__ << endl;
//		cout << "Error :" << e.what() << endl;
//		cout << "MySQL ErrorCode :" << e.getErrorCode() << endl;
//		cout << "SQLState :" << e.getSQLState() << endl;
//	}
//
//
//	return 0;
//}


// ����° �ڵ�
//#ifdef _DEBUG
//#pragma comment(lib, "./mysql-connector/lib64/debug/vs14/mysqlcppconn.lib")
//#else
//#pragma comment(lib, "./mysql-connector/lib64/vs14/mysqlcppconn.lib")
//#endif
//
//
//#include <string>
//#include <iostream>
//#include <exception>
//#include <vector>
//#include <Windows.h>
//
//#include "jdbc/mysql_driver.h"   
//#include "jdbc/mysql_connection.h"
//#include "jdbc/cppconn/statement.h"
//#include "jdbc/cppconn/prepared_statement.h"
//#include "jdbc/cppconn/resultset.h"
//#include "jdbc/cppconn/exception.h"
//
//using namespace std;
//
//std::string Utf8ToMultiByte(std::string utf8_str);
//std::string MultiByteToUtf8(std::string multibyte_str);
//
//class customexeception : exception
//{
//public:
//	customexeception(string what)
//	{
//		message = what;
//	}
//
//	string message;
//};
//
//int main()
//{
//	//try
//	//{
//	//	char* p = nullptr;
//
//	//	cout << 1 << endl;
//	//	//throw customexeception("�̰� �׽�Ʈ ����");
//	//	cout << 2 << endl;
//	//	
//	//	vector<int> a;
//
//	//	a.resize(-1);
//
//	//}
//	//catch (customexeception& e)
//	//{
//	//	cout << e.message << endl;
//	//}
//	//catch ( exception& e)
//	//{
//	//	cout << e.what() << endl;
//	//}
//
//
//	try
//	{
//		sql::Driver* driver = nullptr;
//		sql::Connection* connection = nullptr;
//		sql::Statement* statement = nullptr;
//		sql::ResultSet* resultSet;
//		sql::PreparedStatement* preparedStatement = nullptr;
//
//		driver = get_driver_instance();
//
//		connection = driver->connect("tcp://127.0.0.1", "root", "qweasd123");
//
//		connection->setSchema("member"); //use
//
//		statement = connection->createStatement();
//
//		resultSet = statement->executeQuery("SELECT * FROM user limit 0, 1000;");
//
//		while (resultSet->next())
//		{
//			cout << resultSet->getInt("no") << " : ";
//			cout << resultSet->getString("user_id") << " : ";
//			cout << resultSet->getString("user_password") << " : ";
//			cout << resultSet->getString("email") << " : ";
//			cout << resultSet->getString("created_at") << " : ";
//			cout << resultSet->getInt("is_del") << endl;
//		}
//
//		char Buffer[1024] = { 0, };
//		//string message;
//
//		cin.getline(Buffer, 1024);
//
//		//string Query = "insert into guestbook (`user_no`, `content`, `create_at`, `read_count`) values ";
//		//Query = Query + "('5', '" + MultiByteToUtf8(message) + "', '2024-11-19', '0');";
//		//statement->execute(Query);
//		preparedStatement = connection->prepareStatement("insert into guestbook(`user_no`, `content`, `create_at`, `read_count`) values ( ? , ? , ? , ? )");
//
//		preparedStatement->setInt(1, 5);
//		preparedStatement->setString(2, MultiByteToUtf8(Buffer));
//		preparedStatement->setDateTime(3, "2024-11-19");
//		preparedStatement->setInt(4, 0);
//		preparedStatement->execute();
//
//		resultSet = statement->executeQuery("SELECT * FROM guestbook; ");
//
//		while (resultSet->next())
//		{
//			for (int i = 1; i <= 5; ++i)
//			{
//				cout << Utf8ToMultiByte(resultSet->getString(i)) << " : ";
//			}
//			cout << endl;
//		}
//
//		delete resultSet;
//		resultSet = nullptr;
//
//		delete statement;
//		statement = nullptr;
//
//		delete preparedStatement;
//		preparedStatement = nullptr;
//
//		delete connection;
//		connection = nullptr;
//
//		driver = nullptr;
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "FILE :" << __FILE__ << endl;
//		cout << "LINE :" << __LINE__ << endl;
//		cout << "Error :" << e.what() << endl;
//		cout << "MySQL ErrorCode :" << e.getErrorCode() << endl;
//		cout << "SQLState :" << e.getSQLState() << endl;
//	}
//
//
//	return 0;
//}



// ��Ĺ��� �ڵ�
//#ifdef _DEBUG
//#pragma comment(lib, "./mysql-connector/lib64/debug/vs14/mysqlcppconn.lib")
//#else
//#pragma comment(lib, "./mysql-connector/lib64/vs14/mysqlcppconn.lib")
//#endif
//
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <WinSock2.h>
//
//#pragma comment(lib, "ws2_32")
//
//#include <string>
//#include <iostream>
//#include <exception>
//#include <vector>
//#include <Windows.h>
//
//#include "jdbc/mysql_driver.h"   
//#include "jdbc/mysql_connection.h"
//#include "jdbc/cppconn/statement.h"
//#include "jdbc/cppconn/prepared_statement.h"
//#include "jdbc/cppconn/resultset.h"
//#include "jdbc/cppconn/exception.h"
//
//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//
//using namespace rapidjson;
//
//using namespace std;
//
//std::string Utf8ToMultiByte(std::string utf8_str);
//std::string MultiByteToUtf8(std::string multibyte_str);
//
//class customexeception : exception
//{
//public:
//	customexeception(string what)
//	{
//		message = what;
//	}
//
//	string message;
//};
//
//int main()
//{
//	try
//	{
//		WSAData wsaData;
//		WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//		SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//		SOCKADDR_IN ListenSock;
//		memset(&ListenSock, 0, sizeof(ListenSock));
//		ListenSock.sin_family = AF_INET;
//		ListenSock.sin_addr.s_addr = INADDR_ANY;
//		ListenSock.sin_port = htons(30000);
//
//		int Result = ::bind(ListenSocket, (SOCKADDR*)&ListenSock, sizeof(ListenSock));
//
//		listen(ListenSocket, 5);
//
//		while (true)
//		{
//			SOCKADDR_IN ClientSock;
//			memset(&ClientSock, 0, sizeof(ClientSock));
//			int ClientSockSize = sizeof(ClientSock);
//			SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSock, &ClientSockSize);
//
//			char Buffer[1024] = { 0, };
//			int RecvBytes = recv(ClientSocket, Buffer, 1024, 0);
//
//
//			Document d;
//			d.Parse(Buffer);
//
//			Value& s = d["code"];
//
//			if (strcmp("login", s.GetString()) == 0)
//			{
//				string user_id = d["user_id"].GetString();
//				string user_password = d["user_password"].GetString();
//
//				sql::Driver* driver = nullptr;
//				sql::Connection* connection = nullptr;
//				sql::Statement* statement = nullptr;
//				sql::ResultSet* resultSet;
//				sql::PreparedStatement* preparedStatement = nullptr;
//
//				driver = get_driver_instance();
//
//				connection = driver->connect("tcp://127.0.0.1", "root", "qweasd123");
//
//				connection->setSchema("member"); //use
//
//				preparedStatement = connection->prepareStatement("select * from member where user_id = ? and user_passsword = sha(?);");
//
//				preparedStatement->setString(1, user_id);
//				preparedStatement->setString(2, user_password);
//
//				resultSet = preparedStatement->executeQuery();
//
//				string ResultJSON = "";
//				if (resultSet->rowsCount() == 0)
//				{
//					//����
//					ResultJSON = "{ \"result\" : \"FAILED\", \"message\" : \"not found\" }";
//				}
//				else
//				{
//					ResultJSON = "{ \"result\" : \"SUCCESSED\", \"message\" : \"found\" }";
//
//				}
//
//				int SendSize = send(ClientSocket, ResultJSON.c_str(), (int)ResultJSON.length(), 0);
//			}
//			else
//			{
//				///
//			}
//
//			closesocket(ClientSocket);
//		}
//
//		closesocket(ListenSocket);
//	}
//	catch (sql::SQLException e)
//	{
//		std::cout << "FILE :" << __FILE__ << endl;
//		std::cout << "LINE :" << __LINE__ << endl;
//		std::cout << "Error :" << e.what() << endl;
//		std::cout << "MySQL ErrorCode :" << e.getErrorCode() << endl;
//		std::cout << "SQLState :" << e.getSQLState() << endl;
//	}
//
//
//
//
//	WSACleanup();
//
//
//	return 0;
//}
//
///*
//* @brief ������ ����ϴ� utf-8 ���ڵ��� window���� ����ϴ� ANSI ���ڵ����� ���� �մϴ�.
//*/
//std::string Utf8ToMultiByte(std::string utf8_str)
//{
//	std::string resultString;
//	char* pszIn = new char[utf8_str.length() + 1];
//	strncpy_s(pszIn, utf8_str.length() + 1, utf8_str.c_str(), utf8_str.length());
//
//	int nLenOfUni = 0, nLenOfANSI = 0;
//	wchar_t* uni_wchar = NULL;
//	char* pszOut = NULL;
//
//	// 1. utf8 Length
//	if ((nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
//		return 0;
//
//	uni_wchar = new wchar_t[nLenOfUni + 1];
//	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));
//
//	// 2. utf8 --> unicode
//	nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);
//
//	// 3. ANSI(multibyte) Length
//	if ((nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
//	{
//		delete[] uni_wchar;
//		return 0;
//	}
//
//	pszOut = new char[nLenOfANSI + 1];
//	memset(pszOut, 0x00, sizeof(char) * (nLenOfANSI + 1));
//
//	// 4. unicode --> ANSI(multibyte)
//	nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, pszOut, nLenOfANSI, NULL, NULL);
//	pszOut[nLenOfANSI] = 0;
//	resultString = pszOut;
//
//	delete[] uni_wchar;
//	delete[] pszOut;
//
//	return resultString;
//}
//
///*
//* @brief window���� ����ϴ� ANSI ���ڵ��� ������ ����ϴ� utf-8 ���ڵ� ���ڵ����� ���� �մϴ�.
//*/
//std::string MultiByteToUtf8(std::string multibyte_str)
//{
//	char* pszIn = new char[multibyte_str.length() + 1];
//	strncpy_s(pszIn, multibyte_str.length() + 1, multibyte_str.c_str(), multibyte_str.length());
//
//	std::string resultString;
//
//	int nLenOfUni = 0, nLenOfUTF = 0;
//	wchar_t* uni_wchar = NULL;
//	char* pszOut = NULL;
//
//	// 1. ANSI(multibyte) Length
//	if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
//		return 0;
//
//	uni_wchar = new wchar_t[nLenOfUni + 1];
//	memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));
//
//	// 2. ANSI(multibyte) ---> unicode
//	nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);
//
//	// 3. utf8 Length
//	if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
//	{
//		delete[] uni_wchar;
//		return 0;
//	}
//
//	pszOut = new char[nLenOfUTF + 1];
//	memset(pszOut, 0, sizeof(char) * (nLenOfUTF + 1));
//
//	// 4. unicode ---> utf8
//	nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
//	pszOut[nLenOfUTF] = 0;
//	resultString = pszOut;
//
//	delete[] uni_wchar;
//	delete[] pszOut;
//
//	return resultString;
//}