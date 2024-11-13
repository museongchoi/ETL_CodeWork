#include "Slime.h"
#include <iostream>
using namespace std;

ASlime::ASlime()
{
}

ASlime::~ASlime()
{
}

void ASlime::Move()
{
	cout << "Slime ";
	AActor::Move();
}
