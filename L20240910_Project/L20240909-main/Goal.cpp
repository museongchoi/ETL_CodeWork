#include "Goal.h"
#include "Engine.h"


AGoal::AGoal()
{
	Depth = EDepth::Actor;
	CollisionType = ECollisionType::Overlap;

	Color = { 0, 0, 255, 0 };

	Surface = SDL_LoadBMP("Data/goal.bmp");
	SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, 255, 255, 255));
	Texture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, Surface);
}

AGoal::~AGoal()
{
}
