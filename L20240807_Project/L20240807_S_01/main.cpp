#include <iostream>
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "Boar.h"
#include "Goblin.h"
#include "Slime.h"

using namespace std;


//혼자 개발하지 않는다.
//남을 믿으면 안됨.
int main()
{
	//vector<int> a;
	//vector<AGoblin*> b1;
	//vector<AGoblin> b2;

	vector<AGoblin*> Goblins;
	vector<ASlime*> Slimes;
	vector<ABoar*> Boars;
	vector<AActor*> Actors;

	APlayer* MyPlayer = new APlayer();

	srand((unsigned int)time(nullptr));
	
	int TotalMonsterCnt = rand() % 6;

	for (int i = 0; i < TotalMonsterCnt; i++)
	{
		int Type = rand() % 3;
		if (Type == 0)
		{
			Actors.push_back(new AGoblin());
		}
		else if (Type == 1)
		{
			Actors.push_back(new ASlime());
		}
		else if (Type == 2)
		{
			Actors.push_back(new ABoar());
		}
	}

	//APlayer* MyPlayer = new APlayer();
	Actors.push_back(new APlayer());

	//for (int i = 0; i < Goblins.size(); ++i)
	//{
	//	//Goblins.push_back(new AGoblin());
	//	Actors.push_back(new AGoblin());
	//}
	//for (int i = 0; i < Slimes.size(); ++i)
	//{
	//	//Slimes.push_back(new ASlime);
	//	Actors.push_back(new ASlime());
	//}
	//for (int i = 0; i < Boars.size(); ++i)
	//{
	//	//Boars.push_back(new ABoar);
	//	Actors.push_back(new ABoar());
	//}

	for (int i = 0; i < Actors.size(); ++i)
	{
		// 부모 글래스가 Actor에 없는 함수(기능)인 Attack은 Player 자식 클래스에만 존재하는 함수이므로 화살표의 방향을 자식으로 바꾸어
		// 자식 클래스 Player에 있는 함수를 사용.
		APlayer* Player = dynamic_cast<APlayer*>(Actors[i]);
		if (Player != nullptr)
		{
			Player->Attack();
		}
		Actors[i]->Move();
	}

	MyPlayer->Move();

	for (int i = 0; i < Goblins.size(); ++i)
	{
		Goblins[i]->Move();
	}
	for (int i = 0; i < Slimes.size(); ++i)
	{
		Slimes[i]->Move();
	}
	for (int i = 0; i < Boars.size();; ++i)
	{
		Boars[i]->Move();
	}

	for (int i = 0; i < Goblins.size(); ++i)
	{
		delete Goblins[i];
	}
	for (int i = 0; i < Slimes.size(); ++i)
	{
		delete Slimes[i];
	}
	for (int i = 0; i < Boars.size(); ++i)
	{
		delete Boars[i];
	}

	Goblins.clear();
	Slimes.clear();
	Boars.clear();


	//srand(time(nullptr));
	////cout << rand() % 6 << endl; // rand() 함수 %6 : 범위 지정

	//int GoblinCnt = rand() % 6;
	//int SlimeCnt = rand() % 6;
	//int BoarCnt = rand() % 6;
	//
	//// 배열 : 쉽게 하는 법.
	//AGoblin* Goblins[6];
	//ASlime* Slimes[6];
	//ABoar* Boars[6];
	//APlayer* MyPlayer = new APlayer();

	//for (int i = 0; i < GoblinCnt; ++i)
	//{
	//	//AGoblin* Gobline = new AGoblin; // 해당 값은 반복문안에 있어 매번 날라간다.
	//	Goblins[i] = new AGoblin;
	//}
	//for (int i = 0; i < SlimeCnt; ++i)
	//{
	//	Slimes[i] = new ASlime;
	//}
	//for (int i = 0; i < BoarCnt; ++i)
	//{
	//	Boars[i] = new ABoar;
	//}

	//MyPlayer->Move();

	//for (int i = 0; i < GoblinCnt; ++i)
	//{
	//	Goblins[i]->Move();
	//}
	//for (int i = 0; i < SlimeCnt; ++i)
	//{
	//	Slimes[i]->Move();
	//}
	//for (int i = 0; i < BoarCnt; ++i)
	//{
	//	Boars[i]->Move();
	//}

	//delete MyPlayer;
	//MyPlayer = nullptr;

	//for (int i = 0; i < GoblinCnt; ++i)
	//{
	//	delete Goblins[i];
	//}
	//for (int i = 0; i < SlimeCnt; ++i)
	//{
	//	delete Slimes[i];
	//}
	//for (int i = 0; i < BoarCnt; ++i)
	//{
	//	delete Boars[i];
	//}

	return 0;
}



//#include <iostream>
//#include <vector>
//#include <random>
//#include "Player.h"
//#include "Monster.h"
//#include "Boar.h"
//#include "Goblin.h"
//#include "Slime.h"
//
//using namespace std;
//
//
////혼자 개발하지 않는다.
////남을 믿으면 안됨.
//int main()
//{
//	APlayer* Player = new APlayer();
//	//AActor* Player = new APlayer();
//
//	vector<AActor*> MonsterSpawn;
//	//vector<AActor*> *MonsterSpawn = new vector<AActor*>;
//
//
//	// Mersenne Twister 엔진을 사용하여 난수 생성
//	random_device rd;  // 하드웨어 기반 시드 (일부 시스템에서는 의사난수)
//	mt19937 gen(rd()); // Mersenne Twister 엔진 초기화
//
//	// 범위 지정 (예: 0부터 5까지)
//	uniform_int_distribution<> distr(0, 5);
//	for (int i = 0; i < 3; i++)
//	{
//		int RandonValue = distr(gen);
//		for (int j = 0; j < RandonValue; j++)
//		{
//			if (i == 0)
//			{
//				MonsterSpawn.push_back(new AGoblin());
//			}
//			else if (i == 1)
//			{
//				MonsterSpawn.push_back(new ASlime());
//			}
//			else if (i == 2)
//			{
//				MonsterSpawn.push_back(new ABoar());
//			}
//		}
//	}
//
//	cout << Player->GetHP() << endl;
//	Player->Move();
//
//	for (int i = 0; i < MonsterSpawn.size(); i++)
//	{
//		MonsterSpawn[i]->Move();
//	}
//
//	delete Player;
//	// 메모리 해제
//	for (AActor* actor : MonsterSpawn) {
//		delete actor;  // 각 포인터가 가리키는 메모리를 해제
//	}
//
//	// 벡터를 비움
//	MonsterSpawn.clear();  // 포인터가 제거된 후 벡터를 비움
//
//
//	return 0;
//}