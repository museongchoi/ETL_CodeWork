#pragma once
#include "Actor.h"
#include "Engine.h"

class APlayer : public AActor
{
public:
	APlayer()
	{
		Depth = EDepth::Actor;
		CollisionType = ECollisionType::Overlap;

		Color = { 0, 255, 0, 0 };

		Surface = SDL_LoadBMP("Data/Player.bmp");
		SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, 255, 0, 255));
		Texture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, Surface);
	}
	virtual ~APlayer()
	{

	}

	virtual void Tick(int KeyCode) override;
};

