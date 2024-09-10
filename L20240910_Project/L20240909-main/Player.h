#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer()
	{
		Depth = EDepth::Actor;
	}
	virtual ~APlayer()
	{

	}

	virtual void Tick(int KeyCode) override;
};

