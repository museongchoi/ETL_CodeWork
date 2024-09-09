#include <iostream>
using namespace std;

int main()
{
	int ch;
	int a, b, c;
	cout << "1. 합계, 2. 곱, 3. 평균 중 연산 작업을 선택 하시오. : ";
	cin >> ch;
	cout << "a, b, c 를 입력하시오. : ";
	cin >> a >> b >> c;


	switch (ch)
	{
		case 1:
			cout << "합계 : " << a + b + c << endl;
			break;
		case 2:
			cout << "곱 : " << a * b * c << endl;
			break;
		case 3:
			//cout << "평균 : " << float (a + b + c) / 3 << endl; // c 스타일 (float)
			cout << "평균 : " << (a + b + c) / 3.f << endl;
			break;
		default:
			cout << "잘못된 연산이 선택 되었습니다.";
			break;
		break;
	}


	return 0;
}