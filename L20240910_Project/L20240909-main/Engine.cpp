#include "Engine.h"

#include <conio.h>
#include <stdio.h>
#include <Windows.h>

#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Wall.h"
#include "Floor.h"
#include "Goal.h"

#include <algorithm>

Engine* Engine::Instance = nullptr;

void Engine::Input()
{
	KeyCode = _getch();
}

void Engine::Render()
{
	system("cls");

	//AllActorofClass->Render();
	//for (int i = 0; i < Actors.size(); ++i)
	//{
	//	Actors[i]->Render();
	//}

	for (const auto& Selected : Actors)
	{
		Selected->Render();
	}

}

void Engine::Run()
{
	while (bIsRunning)
	{
		Input();

		Tick();

		Render();
	}
}

void Engine::SpawnActor(AActor* SpawnedActor)
{
	Actors.push_back(SpawnedActor);
}

void Engine::LoadLevel(char Map[10][10])
{
	for (int Y = 0; Y < 10; ++Y)
	{
		for (int X = 0; X < 10; ++X)
		{
			if (Map[Y][X] == '*')
			{
				AWall* Wall = new AWall();
				Wall->SetX(X);
				Wall->SetY(Y);
				Wall->SetStaticMesh(Map[Y][X]);
				GEngine->SpawnActor(Wall);
			}
			else if (Map[Y][X] == 'P')
			{
				APlayer* MyPlayer = new APlayer();
				MyPlayer->SetX(X);
				MyPlayer->SetY(Y);
				MyPlayer->SetStaticMesh(Map[Y][X]);
				GEngine->SpawnActor(MyPlayer);
			}
			else if (Map[Y][X] == 'M')
			{
				AMonster* Monster = new AMonster();
				Monster->SetX(X);
				Monster->SetY(Y);
				Monster->SetStaticMesh(Map[Y][X]);
				GEngine->SpawnActor(Monster);
			}
			else if (Map[Y][X] == ' ')
			{
				AFloor* Floor = new AFloor();
				Floor->SetX(X);
				Floor->SetY(Y);
				Floor->SetStaticMesh(Map[Y][X]);
				GEngine->SpawnActor(Floor);
			}
			else if (Map[Y][X] == 'G')
			{
				AGoal* Goal = new AGoal();
				Goal->SetX(X);
				Goal->SetY(Y);
				Goal->SetStaticMesh(Map[Y][X]);
				GEngine->SpawnActor(Goal);
			}
		}
	}
	// 정렬 1
	//for (int i = 0; i < Actors.size(); i++)
	//{
	//	for (int j = 0; j < Actors.size(); j++)
	//	{
	//		if ((int)Actors[i]->GetDepth() < (int)Actors[j]->GetDepth())
	//		{
	//			AActor* Temp = Actors[i];
	//			Actors[i] = Actors[j];
	//			Actors[j] = Temp;
	//		}
	//	}
	//}

	// 정렬 2
	//std::sort(Actors.begin(), Actors.end(), AActor::Compare);

	// 정렬 3
	std::sort(Actors.begin(), Actors.end(), [&](AActor* A, AActor* B)
		{
			return (int)A->GetDepth() < (int)B->GetDepth();
		});

	// 내 정렬 코드
	//std::sort(Actors.begin(), Actors.end(), [](AActor* A, AActor* B)
	//{
	//	return static_cast<int>(A->GetDepth()) < static_cast<int>(B->GetDepth());
	//});

}

void Engine::Tick()
{
	//AllActorofClass->Tick();

	if (KeyCode == 27)
	{
		bIsRunning = false;
	}

	for (int i = 0; i < Actors.size(); ++i)
	{
		Actors[i]->Tick(KeyCode);
	}
}