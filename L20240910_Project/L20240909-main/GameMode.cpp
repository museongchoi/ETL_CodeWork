#include "GameMode.h"
#include "Engine.h"
#include "Player.h"
#include "Monster.h"
#include "Goal.h"

AGameMode::AGameMode()
{
	Depth = EDepth::GameSystem;
}

AGameMode::~AGameMode()
{
}

void AGameMode::Tick(int KeyCode)
{
	//APlayer* Player = nullptr;
	//AGoal* Goal = nullptr;
	//AMonster* Monster = nullptr;

	if (Player->GetX() == Monster->GetX() && Player->GetY() == Monster->GetY())
	{
		GEngine->Stop();
	}

	if (Player->GetX() == Goal->GetX() && Player->GetY() == Goal->GetY())
	{
		GEngine->Stop();
	}
}

// 아무것도 표시하지 않으므로 아무것도 처리하지 않는다.
void AGameMode::Render()
{
}

void AGameMode::BeginPlay()
{
	// Tick 에서 이동 : 매 프레임 마다 검사하는 것은 비효율적이다.
	for (auto& SelectedActor : GEngine->GetActors())
	{
		if (dynamic_cast<APlayer*>(SelectedActor))
		{
			Player = dynamic_cast<APlayer*>(SelectedActor);
		}
		if (dynamic_cast<AGoal*>(SelectedActor))
		{
			Goal = dynamic_cast<AGoal*>(SelectedActor);
		}
		if (dynamic_cast<AMonster*>(SelectedActor))
		{
			Monster = dynamic_cast<AMonster*>(SelectedActor);
		}
	}
}
