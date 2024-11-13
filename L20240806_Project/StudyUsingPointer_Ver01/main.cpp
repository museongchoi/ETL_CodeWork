#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// 포인터와 참조연산자.
	int a = 10;

	int* ptr = &a;

	cout << ptr;

	// int 와는 별개라고 생각하는게 외우기 쉬움.
	int* P = new int;

	cout << sizeof(P) << endl;
	cout << new int << endl; // 메모리 위치값 | 새로 할당한 메모리 위치

	delete P;

	cout << "--------------" << endl;

	// 단순 무식
	int Korean1 = 89;
	int Korean2 = 89;
	int Korean3 = 89;
	int Korean4 = 89;
	int Korean5 = 89;

	// 대표명으로 시작 주소를 알려준다.
	//int Korean[10] = { 0, }; // {} : 초기화
	int Korean[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	cout << Korean << endl; // 배열 이름은 위치값
	cout << Korean[0] << endl;
	cout << &Korean[0] << endl;
	cout << &Korean[1] << endl;

	cout << *Korean << endl;
	// 포인터 연산과 배열의 접근 방법
	// 배열의 원형 : 원형을 편하게 사용하기 위함
	cout << *(Korean + 0 * sizeof(int)) << endl;
	cout << *(Korean + 1) << endl;
	cout << (int long)(Korean + 1) << endl;

	// 배열을 여러번 반복하기 위해 문법이 만들어진것
	cout << Korean[0] << endl;
	cout << Korean[1] << endl;

	// 만들어진 문법 예 : 배열에 접근하기 위해 만들어진 문법
	for (int i = 0; i < 10; ++i)
	{
		cout << Korean[i] << endl;
	}

	return 0;
}