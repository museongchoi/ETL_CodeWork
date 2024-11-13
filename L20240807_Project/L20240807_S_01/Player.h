#pragma once
#include "Actor.h"

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	virtual void Move() override;

	void Attack();
};

