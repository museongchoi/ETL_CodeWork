#include "Player.h"
#include <iostream>
using namespace std;


APlayer::APlayer()
{
	cout << "Player 생성자" << endl;
	HP = 100;
}

APlayer::~APlayer()
{
	cout << "Player 소멸자" << endl;
}

void APlayer::Move()
{
	cout << "Player 이동" << endl;
}
