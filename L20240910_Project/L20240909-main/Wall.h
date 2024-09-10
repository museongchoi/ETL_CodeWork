#pragma once
#include "Actor.h"
class AWall : public AActor
{
public:
	AWall()
	{
		Depth = EDepth::Actor;
		CollisionType = ECollisionType::Collision;
	}

	virtual ~AWall()
	{

	}
};

