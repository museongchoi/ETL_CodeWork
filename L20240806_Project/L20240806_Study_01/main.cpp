#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "Boar.h"
#include "Goblin.h"

using namespace std;


// 혼자 개발하지 않는다. 남을 믿으면 안된다.
int main()
{
	APlayer* Player = new APlayer();
	cout << Player->GetHP() << endl;

	delete Player;

	return 0;
}

// 유산
//APlayer Player; // 컴파일 단계에서 정의가 된다.
//APlayer* Player; // 생성이 아닌 플레이어를 가르키는 8바이트 화살표
//new APlayer; // 
//APlayer* Player = new APlayer; // new 연산자를 사용한 생성자를 저장. | 원할때 생성 원할때 소멸

//Player->Move();
//AMonster* Monster = new AMonster;
//
//Monster->Move();

//delete Player;
//delete Monster;
//ABoar* Boar = new ABoar; // 상속을 받은 클래스는 부모먼저 메모리가 잡히며 생성
//
//Boar->Move();
//
//delete Boar;
//
//AGoblin* Goblin = new AGoblin;
//
//Goblin->Move();
//
//delete Goblin;



//AActor* Actor = new AActor;
////Actor->HP = 0; // AActor 클래스 안에 private에 HP를 선언하지 않으면 접근제어. 즉, 관리가 되지 않기 때문에 다른 관리자가 접근을 하는 불상사 발생.
//
//delete Actor;