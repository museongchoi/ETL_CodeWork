#include "Monster.h"
#include <stdlib.h>
#include <time.h>

AMonster::AMonster()
{
	srand((unsigned int)time(nullptr));
	Depth = EDepth::Actor;
}

void AMonster::Tick(int KeyCode)
{
	int Diredction = rand() % 4;

	if (Diredction == 0)
	{
		Y--;
	}
	else if (Diredction == 1)
	{
		X--;
	}
	else if (Diredction == 2)
	{
		Y++;
	}
	else //if (Diredction == 3)
	{
		X++;
	}
}