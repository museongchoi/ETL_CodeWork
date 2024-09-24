#include "Goal.h"

AGoal::AGoal()
{
	Depth = EDepth::Actor;
	CollisionType = ECollisionType::Overlap;

	Color = { 0, 0, 255, 0 };
}

AGoal::~AGoal()
{
}
