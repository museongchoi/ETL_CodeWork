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
#include "SDL.h"

#include <algorithm>

#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

Engine* Engine::Instance = nullptr;


Engine::Engine()
{
	KeyCode = 0;
	bIsRunning = true;
	bWillStop = false;

	Init();
}

void Engine::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	MyWindow = SDL_CreateWindow("HelloWorld", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	//SDL_Renderer* MyRenderer =  SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
}

void Engine::Term()
{
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);

	SDL_Quit();
}

Engine::~Engine()
{
	for (auto& Actor : Actors)
	{
		delete Actor;
	}

	Actors.clear();
	Term();
}

void Engine::Input()
{
	KeyCode = _getch();
	SDL_PollEvent(&MyEvent);
}

void Engine::Render()
{
	system("cls");
	SDL_SetRenderDrawColor(MyRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(MyRenderer);

	//AllActorofClass->Render();
	//for (int i = 0; i < Actors.size(); ++i)
	//{
	//	Actors[i]->Render();
	//}

	for (const auto& Selected : Actors)
	{
		Selected->Render();
	}

	SDL_RenderPresent(MyRenderer);
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
	BeginPlay(); // 엔진 Run 시작 시 제일 처음 실행
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
	// GameMode 가 엑터이므로 레벨에 생성. 해당 레벨에 생성될때 모양과 위치를 잡아줘야한다.

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
			//else if (Line[X] == ' ')
			//{
			//	AFloor* Floor = new AFloor();
			//	Floor->SetX(X);
			//	Floor->SetY(Y);
			//	Floor->SetStaticMesh(Line[X]);
			//	GEngine->SpawnActor(Floor);
			//}
			else if (Line[X] == 'G')
			{
				AGoal* Goal = new AGoal();
				Goal->SetX(X);
				Goal->SetY(Y);
				Goal->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(Goal);
			}
			if (Line[X] != '\n')
			{
				AFloor* Floor = new AFloor();
				Floor->SetX(X);
				Floor->SetY(Y);
				Floor->SetStaticMesh(Line[X]);
				GEngine->SpawnActor(Floor);
			}
		}
		Y++;
	}

	fclose(MapFile);


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
	switch (MyEvent.type)
	{
		bIsRunning = false;
	case SDL_QUIT:
		Stop();
	case SDL_KEYDOWN:
		switch (MyEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			Stop();
		}
	}
	//if (KeyCode == 27)
	//{
	//	bIsRunning = false;
	//}

	for (int i = 0; i < Actors.size(); ++i)
	{
		Actors[i]->Tick(KeyCode);
	}
}