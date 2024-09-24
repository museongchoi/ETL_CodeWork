#pragma once
#include "Actor.h"
class AWall : public AActor
{
public:
	AWall()
	{
		Depth = EDepth::Actor;
		CollisionType = ECollisionType::Collision;
		Color = { 128, 128, 128, 0 };
	}

	virtual ~AWall()
	{

	}
};

