#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer()
	{

	}
	virtual ~APlayer()
	{

	}

	virtual void Tick(int KeyCode) override;
};