#include "Player.h"
#include "Engine.h"

void APlayer::Tick(int KeyCode)
{
	if (GEngine->MyEvent.type == SDL_KEYDOWN)
	{
		SDL_Keycode MyKeyCode = GEngine->MyEvent.key.keysym.sym;
		if (MyKeyCode == SDLK_w || MyKeyCode == SDLK_UP)
		{
			if (PredictCollision(X, Y - 1))
			{
				Y--;
			}
		}
		if (MyKeyCode == SDLK_a || MyKeyCode == SDLK_LEFT)
		{
			if (PredictCollision(X - 1, Y))
			{
				X--;
			}
		}
		if (MyKeyCode == SDLK_s || MyKeyCode == SDLK_DOWN)
		{
			if (PredictCollision(X, Y + 1))
			{
				Y++;
			}
		}
		if (MyKeyCode == SDLK_d || MyKeyCode == SDLK_RIGHT)
		{
			if (PredictCollision(X + 1, Y))
			{
				X++;
			}
		}
	}
}

