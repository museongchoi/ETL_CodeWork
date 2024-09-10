#include "Player.h"

void APlayer::Tick(int KeyCode)
{
	if (KeyCode == 'w')
	{
		Y--;
	}
	if (KeyCode == 'a')
	{
		X--;
	}
	if (KeyCode == 's')
	{
		Y++;
	}
	if (KeyCode == 'd')
	{
		X++;
	}
}
