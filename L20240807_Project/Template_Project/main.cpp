#include <iostream>
using namespace std;

//template : 자료형, 타입을 변수로 변경. template함수
//Compile 할때 코드 생성
template <typename T>
class Data
{
public:
	T Value;
	T Add();

};

// T가 무엇인지 모른다. 각 template를 사용해야함. 그러므로 해당 함수나 클래스 내부에서작성을 해야한다.
//T Add()
//{
//
//}

// 위 T와 별개 T이다.
template <typename T>
// overloading
T Add(T A, T B)
{
	return A + B;
}
char Add(char A, char B)
{
	return A + B;
}

float Add(float A, float B)
{
	return A + B;
}

int Add(int A, int B)
{
	return A + B;
}


int main()
{
	cout << Add<int>(1, 2) << endl;
	cout << Add<float>(1.1f, 2.3f) << endl;
	//cout << Add(1, 2.3f) << endl;
	cout << Add<char>('A', 'B') << endl; //<> : 자료형을 받겠다. == template
	cout << Add<double>(1.1f, 2.3f) << endl;


	return 0;
}