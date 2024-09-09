#include <iostream>
using namespace std;

int main()
{
	int Number1 = 0;
	int Number2 = 0;

	//cout << (char)10; == "\n";
	//cout << endl;

	cin >> Number1 >> Number2;

	int Add = Number1 + Number2;
	int Sub = Number1 - Number2;
	int Dic = Number1 * Number2;
	int Mul = Number1 / Number2;
	int Remainder = Number1 % Number2;

	cout << Number1 + Number2 << "\n";
	cout << Number1 - Number2 << "\n";
	cout << Number1 * Number2 << "\n";
	cout << Number1 / Number2 << "\n";
	cout << Number1 % Number2 << "\n";
	cout << "\n";

	cout << Add << "\n";
	cout << Sub << "\n";
	cout << Dic << "\n";
	cout << Mul << "\n";
	cout << Remainder << "\n";

	return 0;
}