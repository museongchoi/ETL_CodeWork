#include "Floor.h"

AFloor::AFloor()
{
	Depth = EDepth::Floor;
	CollisionType = ECollisionType::NoCollision;

	Color = { 185, 122, 87, 255 };
}

AFloor::~AFloor()
{
}
