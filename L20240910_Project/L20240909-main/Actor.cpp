#include "Actor.h"
#include <Windows.h>
#include <stdio.h>

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
