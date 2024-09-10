#pragma once
#include "Actor.h"
class AWall : public AActor
{
public:
	AWall()
	{
		Depth = EDepth::Actor;
	}

	virtual ~AWall()
	{

	}
};

