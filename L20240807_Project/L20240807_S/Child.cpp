#include <iostream>
#include "Child.h"

Child::Child()
{
}

Child::~Child()
{
}

void Child::Investment()
{
	srand((unsigned int)(time(nullptr)));
	Money = (rand() % 2) == 1 ? Money * 2 : 0;
}
