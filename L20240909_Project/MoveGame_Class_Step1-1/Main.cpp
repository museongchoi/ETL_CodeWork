#include "Engine.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
using namespace std;

int main()
{
	Engine MyEngine;

	APlayer* MyPlayer = new APlayer();
	MyPlayer->SetX(5);
	MyPlayer->SetY(8);
	MyPlayer->SetStaticMesh('P');

	MyEngine.SpawnActor(MyPlayer);

	AMonster* MyMonster = new AMonster();
	MyMonster->SetX(20);
	MyMonster->SetY(20);
	MyMonster->SetStaticMesh('M');

	MyEngine.SpawnActor(MyMonster);

	MyEngine.Run();

	cout << "종료 되었습니다.";
	return 0;
}

//#include <iostream>
//#include <conio.h>
//#include <Windows.h>
//using namespace std;
//
//char Key = 0;
//int PlayerX = 0;
//int PlayerY = 0;
//
//void Input()
//{
//	Key = _getch();
//
//}
//void Tick()
//{
//	if (Key == 'w')
//	{
//		PlayerY--;
//	}
//	if (Key == 's')
//	{
//		PlayerY++;
//	}
//	if (Key == 'a')
//	{
//		PlayerX--;
//	}
//	if (Key == 'd')
//	{
//		PlayerX++;
//	}
//}
//void Render()
//{
//	system("cls");
//	COORD Cur;
//	Cur.X = PlayerX;
//	Cur.Y = PlayerY;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
//	cout << "*";
//}
//
//int main()
//{
//	while (true)
//	{
//		Input();
//		Tick();
//		Render();
//	}
//
//	return 0;
//}