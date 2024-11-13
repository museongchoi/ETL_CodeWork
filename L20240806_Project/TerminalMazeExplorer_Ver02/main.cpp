#include <iostream>
#include <conio.h>
using namespace std;

// 다차원 배열 int Map[10][10][10]; : 3차원은 메모리 낭비가 많음.
int Map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

int PlayerX = 1;
int PlayerY = 1;
char Key;
bool bIsRunning = true;


void Rander()
{
	system("cls"); // 작업에 쓰지말기.

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (x == PlayerX && y == PlayerY)
			{
				cout << "P";
			}
			else if (Map[y][x] == 1)
			{
				cout << "#";
			}
			else if (Map[y][x] == 0)
			{
				cout << " ";
			}
			//cout << Map[y][x];
		}
		cout << endl; // 벽 : #, 바닥 : " "
	}
}

void Process()
{
	if (Key == 'w')
	{
		PlayerY--;
	}
	if (Key == 's')
	{
		PlayerY++;
	}
	if (Key == 'a')
	{
		PlayerX--;
	}
	if (Key == 'd')
	{
		PlayerX++;
	}
	if (Key == 'q')
	{
		bIsRunning = false;
	}
}

void Input()
{
	//cin >> Key;
	Key = _getch();
}

// 절차지향프로그래밍 - 협업에서 문제점. 해당 변수의 접근 제어가 되지 않아 문제가 생기고, 구조 파악이 어렵다.
// ->
// 객체지향프로그래밍 - 
int main()
{
	// Engine, Game Loop
	//for(;;)
	while (bIsRunning)
	{
		Input();

		Process();

		Rander();
	}



	return 0;
}


//#include <iostream>
//#include <conio.h>
//
//using namespace std;
//
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
////[][][][][][][][][][]
//
//int Map[10][10] = {
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
//};
//
//int PlayerX = 1;
//int PlayerY = 1;
//char Key;
//bool bIsRunning = true;
//
//
//
//
//void Render()
//{
//	system("cls");
//
//	for (int Y = 0; Y < 10; ++Y)
//	{
//		for (int X = 0; X < 10; ++X)
//		{
//			if (X == PlayerX && Y == PlayerY)
//			{
//				cout << "P";
//			}
//			else if (Map[Y][X] == 1)
//			{
//				cout << "#";
//			}
//			else if (Map[Y][X] == 0)
//			{
//				cout << " ";
//			}
//		}
//		cout << endl; //#, " "
//	}
//}
//
//void Input()
//{
//	Key = _getch();
//}
//
//void Process()
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
//	if (Key == 'q')
//	{
//		bIsRunning = false;
//	}
//}
//
//
//int main()
//{
//	while (bIsRunning)
//	{
//		Input();
//
//		Process();
//
//		Render();
//	}
//
//	return 0;
//}
