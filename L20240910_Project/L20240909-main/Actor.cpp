#include "Actor.h"
#include <Windows.h>
#include <stdio.h>
#include "Engine.h"


AActor::AActor()
{
	X = 10;
	Y = 10;
	Depth = EDepth::Background;
	CollisionType = ECollisionType::NoCollision;
	Color = { 255, 255, 255, 255 };
	SizeX = 60;
	SizeY = 60;
}

AActor::~AActor()
{
}

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

	SDL_SetRenderDrawColor(GEngine->MyRenderer, Color.r, Color.g, Color.b, Color.a);
	SDL_Rect PositionRect = { X * SizeX, Y * SizeY, SizeX, SizeY };
	SDL_RenderFillRect(GEngine->MyRenderer, &PositionRect);
}

void AActor::BeginPlay()
{
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



