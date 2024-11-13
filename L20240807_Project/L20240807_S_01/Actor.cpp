#include "Actor.h"
#include <iostream>

using namespace std;
AActor::AActor()
{

}

AActor::~AActor()
{
}

void AActor::Move()
{
	cout << "ÀÌµ¿" << endl;
	HP = 100;
}
