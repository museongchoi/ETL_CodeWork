// 전처리 과정
// < > : 표준 | " " : 새로운 정의 사용
#include <iostream>
#include "Parent.h"
#include "Child.h"
using namespace std; // 다른 클래스에서 std 에서 사용하는 명은 쓰지 않는것이 좋다.
//using namespace Choi;

// 클래스화 꼭!!!
//class Parent
//{
//public:
//	Parent(); // 생성자
//	~Parent(); // 섬멸자
//};

//endtry point
int main()
{
	std::cout << "Hello World~" << std::endl;

	//Parent P;
	Parent* P = new Child;
	P->SetMoney(100);
	cout << P->GetMoney() << endl;
	P->Investment();
	cout << P->GetMoney() << endl;



	//P.Money = -100; // private에 선언되어 접근 불가
	//private 에 선언되었기에 get으로 들고올수있는 기능밖에 못함

	//P.SetMoney(100);
	//cout << P.GetMoney() << endl;

	//Child C;
	//C.SetMoney(100);
	//cout << C.GetMoney() << endl;

	//C.Investment();
	//cout << C.GetMoney() << endl;

	//Child is a Parent
	//Apple is Fruit
	//Goblin is Monster

	//Choi::Parent p;
	return 0;
}