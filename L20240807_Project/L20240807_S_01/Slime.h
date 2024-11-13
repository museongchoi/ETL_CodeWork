#pragma once
#include "Actor.h"
class ASlime : public AActor
{
public:
	ASlime();
	~ASlime();

	virtual void Move() override;

};

