#include "Monster.h"
#include <stdlib.h>
#include <time.h>

AMonster::AMonster()
{
	srand((unsigned int)time(nullptr));
}

void AMonster::Tick(int KeyCode)
{
	int Diredction = rand() % 4;

	if (Diredction == 0)
	{
		Y--;
	}
	if (Diredction == 1)
	{
		X--;
	}
	if (Diredction == 2)
	{ 
		Y++;
	}
	if (Diredction == 3)
	{
		X++;
	}
}
