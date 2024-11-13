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
	cout << "Player ";
	AActor::Move();

}

void APlayer::Attack()
{
	cout << "Player가 공격 한다." << endl;
}
