#pragma once
#include <vector>
//#include "Player.h"
class APlayer; // 필요할때 해당 class를 찾아서 써라 | 게임을 종료할때까지 가지고 있는 다는 것이므로 가능하다.
class AMonster;
class AGoal;
class AFloor;
class AWall;

class UWorld
{
public:
	// 무조건 생성자 섬멸자 호출
	UWorld(); // 생성자
	~UWorld(); // 섬멸자


	//APlayer Player; // "Player.h 헤드파일 선언 후 변수로 생성할 경우 : 생성하자마자 메모리가 잡힌다.
	APlayer* Player;
	AMonster* Monster;
	std::vector<AFloor*> Floors; // 바닥
	std::vector<AWall*> Walls; // 벽

	AGoal* Goal; // 목적지

};

