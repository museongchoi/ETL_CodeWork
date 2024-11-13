#include "Engine.h"
#include "World.h"
#include "Wall.h"
#include "Floor.h"
#include "Player.h"
#include "Goal.h"
#include "Monster.h"

UEngine::UEngine()
{
}

UEngine::~UEngine()
{
}

void UEngine::OpenLevel()
{
	// fopen? | 1. Memory(Array), 2. Disk(File), 3. NetWork
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

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (Map[y][x] == 1)
			{
				World->Walls.push_back(new AWall());

			}
			else if (Map[y][x] == 0)
			{
				World->Floors.push_back(new AFloor());
			}
		}
	}

	World->Player = new APlayer();
	World->Goal = new AGoal();
	World->Monster = new AMonster();
}

void UEngine::Run()
{
	/*while (true)
	{

	}*/
}
