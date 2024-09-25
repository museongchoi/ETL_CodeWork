#pragma once
#include "Actor.h"
#include "Engine.h"

class APlayer : public AActor
{
public:
	enum class EPlayerDirection
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
	};

	APlayer()
	{
		Depth = EDepth::Actor;
		CollisionType = ECollisionType::Overlap;

		Color = { 0, 255, 0, 0 };

		Surface = SDL_LoadBMP("Data/Player.bmp");
		SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, 255, 0, 255));
		Texture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, Surface);
		Direction = EPlayerDirection::Left;
	}
	virtual ~APlayer()
	{

	}

	virtual void Tick(int KeyCode) override;
	virtual void Render() override;

	Uint64 ElapsedTime;
	Uint64 ProcessTime;

	EPlayerDirection Direction;
};

