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
				Direction = EPlayerDirection::Up;
				Y--;
			}
		}
		if (MyKeyCode == SDLK_a || MyKeyCode == SDLK_LEFT)
		{
			if (PredictCollision(X - 1, Y))
			{
				Direction = EPlayerDirection::Left;
				X--;
			}
		}
		if (MyKeyCode == SDLK_s || MyKeyCode == SDLK_DOWN)
		{
			if (PredictCollision(X, Y + 1))
			{
				Direction = EPlayerDirection::Down;
				Y++;
			}
		}
		if (MyKeyCode == SDLK_d || MyKeyCode == SDLK_RIGHT)
		{
			if (PredictCollision(X + 1, Y))
			{
				Direction = EPlayerDirection::Right;
				X++;
			}
		}
	}
}

void APlayer::Render()
{
	//AActor::Render();
	SDL_SetRenderDrawColor(GEngine->MyRenderer, Color.r, Color.g, Color.b, Color.a);
	SDL_Rect PositionRect = { X * SizeX, Y * SizeY, SizeX, SizeY };
	int tmp = 0;

	if (Texture == nullptr)
	{
		SDL_RenderFillRect(GEngine->MyRenderer, &PositionRect);
	}
	else
	{
		//int Direction = 0; // ¸â¹ö º¯¼ö
		int TotalFrame = 5;
		int AnimationTime = 200;

		int SpritSizeX = Surface->w / TotalFrame;
		int SpritSizey = Surface->h / TotalFrame;

		//int Width = Surface->w;
		//int Height = Surface->h;

		static int SpriteIndex = 0;
		static Uint64 ElapsedTime = 0;

		ElapsedTime += GEngine->GetWorldDeltaSeconds();
		if (ElapsedTime >= AnimationTime)
		{
			ElapsedTime = 0;
			SpriteIndex++;
			SpriteIndex = SpriteIndex % TotalFrame;
		}

		SDL_Rect SourceRect = { SpritSizeX * SpriteIndex, SpritSizey * (int)Direction, SpritSizeX, SpritSizey };
		SDL_RenderCopy(GEngine->MyRenderer, Texture, &SourceRect, &PositionRect);
	}
}

