#pragma once
#include "Actor.h"
class AMonster : public AActor
{
public:
	AMonster();
	virtual ~AMonster()
	{

	}

	virtual void Tick(int KeyCode) override;

	Uint64 ElapsedTime;
	Uint64 ProcessTime;

};

