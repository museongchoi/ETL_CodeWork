#include "Monster.h"
#include <stdlib.h>
#include <time.h>
#include "Engine.h"

AMonster::AMonster()
{
	srand((unsigned int)time(nullptr));
	Depth = EDepth::Actor;
	CollisionType = ECollisionType::Overlap;

	Color = { 255, 0, 0, 0 };

	ElapsedTime = 0;
	ProcessTime = 500;
}

void AMonster::Tick(int KeyCode)
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ElapsedTime < ProcessTime)
	{
		return;
	}

	ElapsedTime = 0;

	int Diredction = rand() % 4;

	if (Diredction == 0)
	{
		if (PredictCollision(X, Y - 1))
		{
			Y--;
		}
	}
	else if (Diredction == 1)
	{
		if (PredictCollision(X - 1, Y))
		{
			X--;
		}
	}
	else if (Diredction == 2)
	{
		if (PredictCollision(X, Y + 1))
		{
			Y++;
		}
	}
	else //if (Diredction == 3)
	{
		if (PredictCollision(X + 1, Y))
		{
			X++;
		}
	}
}