#include "Player.h"

void APlayer::Tick(int KeyCode)
{
	if (KeyCode == 'w')
	{
		if (PredictCollision(X, Y - 1))
		{
			Y--;
		}
	}
	if (KeyCode == 'a')
	{
		if (PredictCollision(X-1, Y))
		{
			X--;
		}
	}
	if (KeyCode == 's')
	{
		if (PredictCollision(X, Y + 1))
		{
			Y++;
		}
	}
	if (KeyCode == 'd')
	{
		if (PredictCollision(X + 1, Y))
		{
			X++;
		}
	}
}

