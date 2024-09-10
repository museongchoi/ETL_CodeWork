#include "Actor.h"
#include <Windows.h>
#include <stdio.h>
#include "Engine.h"

void AActor::Tick(int KeyCode)
{
}

void AActor::Render()
{
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	printf("%c", GetStaticMesh());
}

bool AActor::PredictCollision(int NewX, int NewY)
{
	for (auto& SelectedActor : GEngine->GetActors())
	{
		if (SelectedActor->GetX() == NewX and SelectedActor->GetY() == NewY)
		{
			if (SelectedActor->CollisionType == ECollisionType::Collision)
			{
				return false;
			}
		}
	}
	return true;
}

