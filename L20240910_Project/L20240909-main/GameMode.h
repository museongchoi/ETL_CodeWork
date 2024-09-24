#pragma once
#include "Actor.h"

class AGameMode : public AActor
{
public:
	AGameMode();
	virtual ~AGameMode();

	virtual void Tick(int KeyCode) override;
	virtual void Render() override;
	virtual void BeginPlay() override;

protected:
	class APlayer* Player;
	class AGoal* Goal;
	class AMonster* Monster;
};

