#include <iostream>
using namespace std;

int main()
{
	// 크기가 작은 것 속도 효율성 up
	double Number0 = 0.1;
	float Number = 0.1f;
	float Number1 = 3.0f;
	float Number2 = 2.0f;

	int Number3 = 3;
	float Number4 = 2.0f;

	cout << Number0 << endl;
	cout << Number << endl;
	cout << Number1 << endl;
	cout << Number2 << endl;
	cout << Number1 / Number2 << endl;
	cout << "\n";

	cout << Number3 / Number4 << endl;

	// 형 변환, 캐스팅, c style
	cout << (float)Number3 / Number4 << endl;
	cout << Number4 / (int)Number4 << endl;

	return 0;
}