#include "Engine.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Wall.h"
#include "Gate.h"
#define MAX_SIZE 10

int main()
{
	APlayer* MyPlayer = new APlayer();
	MyPlayer->SetX(2);
	MyPlayer->SetY(2);
	MyPlayer->SetStaticMesh('P');
	GEngine->SpawnActor(MyPlayer);

	AMonster* Monster = new AMonster();
	Monster->SetX(5);
	Monster->SetY(5);
	Monster->SetStaticMesh('M');
	GEngine->SpawnActor(Monster);

	AGate* Gate = new AGate();
	Gate->SetX(8);
	Gate->SetY(8);
	Gate->SetStaticMesh('G');
	GEngine->SpawnActor(Gate);


	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 9)
			{
				AWall* Wall = new AWall();
				Wall->SetX(i);
				Wall->SetY(j);
				Wall->SetStaticMesh('*');
				GEngine->SpawnActor(Wall);
			}
		}
	}
	

	GEngine->Run();

	return 0;
}