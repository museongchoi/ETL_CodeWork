#include <iostream> // 표준 사용
// "iostream" 자신이 작성한 헤더파일
using namespace std;	// 사용, 이름 공간, std 클래스 안에 입출력 사용

// entry point - 시작 포인트
// main 함수 반환형 int, 반환값은 0 / main 은 하나, main 시작점 처음 실행 점
int main()
{
	// 상수 const : 변하지 않는 값
	cout << 1 << "\n"; // 정수형
	cout << 1.1f << endl; // f 실수형

	// 사칙 연산
	cout << 1 + 1 << "\n";
	cout << 1 * 1 << "\n";
	cout << 1 / 1 << "\n";
	cout << 1 % 1 << "\n";

	// 변수 선언 - 메모리 공간에 위치 정보를 저장 하는 이름을 가진 저장 공간. + 변수의 데이터 타입
	// 파스칼 케이싱 - 언리얼 스타일 첫 문자 대문자 다음 첫문자 대문자

	// 메모리 어딘가에 각 4byte 정수를 저장 - 2의 64승 (64비트)
	int MyMoney; // 선언
	MyMoney = 10; // 초기화
	int MyGold = 100; // 선언 + 초기화

	cout << MyMoney << "\n";

	int HP = 0;
	int Damage = 0;
	int Gold = 0;

	HP = 100;
	Damage = 10;
	Gold = 1;

	// 공격
	cout << HP - Damage << "\n";

	// 힐
	cout << HP + Damage << "\n";
	cout << &HP << "\n"; // & - 주소값

	// 만약 적이랑 만나면
	// 만약 공격 당하면

	return 0;
}