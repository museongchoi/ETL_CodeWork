#define _CRT_SECURE_NO_WARNINGS
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
#include "GameMode.h"

#include <algorithm>

Engine* Engine::Instance = nullptr;

Engine::~Engine()
{
	for (auto& Actor : Actors)
	{
		delete Actor;
	}

	Actors.clear();
}

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

void Engine::BeginPlay()
{
	for (const auto& Selected : Actors)
	{
		Selected->BeginPlay();
	}
}

void Engine::Run()
{
	BeginPlay(); // ���� Run ���� �� ���� ó�� ����
	while (bIsRunning)
	{
		Input();

		Tick();

		Render();

		if (bWillStop)
		{
			bIsRunning = true;
			break;
		}
	}
}

void Engine::SpawnActor(AActor* SpawnedActor)
{
	Actors.push_back(SpawnedActor);
}

void Engine::LoadLevel(const char* MapName)
{
	GEngine->SpawnActor(new AGameMode()); 
	// GameMode �� �����̹Ƿ� ������ ����. �ش� ������ �����ɶ� ���� ��ġ�� �������Ѵ�.

	FILE* MapFile = fopen(MapName, "r");

	char Line[100] = { 0, };
	int Y = 0;

	while (fgets(Line, 100, MapFile) != nullptr)
	{
		for (int X = 0; X < strlen(Line); ++X)
		{
			if (Line[X] == '*')
			{
				AWall* Wall = new AWall();
				Wall->SetX(X);
				Wall->SetY(Y);
				Wall->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(Wall);
			}
			else if (Line[X] == 'P')
			{
				APlayer* MyPlayer = new APlayer();
				MyPlayer->SetX(X);
				MyPlayer->SetY(Y);
				MyPlayer->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(MyPlayer);
			}
			else if (Line[X] == 'M')
			{
				AMonster* Monster = new AMonster();
				Monster->SetX(X);
				Monster->SetY(Y);
				Monster->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(Monster);
			}
			else if (Line[X] == ' ')
			{
				AFloor* Floor = new AFloor();
				Floor->SetX(X);
				Floor->SetY(Y);
				Floor->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(Floor);
			}
			else if (Line[X] == 'G')
			{
				AGoal* Goal = new AGoal();
				Goal->SetX(X);
				Goal->SetY(Y);
				Goal->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(Goal);
			}
		}
		Y++;
	}

	fclose(MapFile);


	// ���� 2
	//std::sort(Actors.begin(), Actors.end(), AActor::Compare);

	// ���� 3
	std::sort(Actors.begin(), Actors.end(), [&](AActor* A, AActor* B)
	{
			return (int)A->GetDepth() < (int)B->GetDepth();
	});

	// �� ���� �ڵ�
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