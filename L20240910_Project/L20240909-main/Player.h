#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer()
	{
		Depth = EDepth::Actor;
		CollisionType = ECollisionType::Overlap;

		Color = { 0, 255, 0, 0 };
	}
	virtual ~APlayer()
	{

	}

	virtual void Tick(int KeyCode) override;
};

