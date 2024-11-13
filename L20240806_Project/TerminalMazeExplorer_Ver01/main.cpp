#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 세상의 벽과 바닥으로 이루어져 있습니다. 벽 1, 바닥 0
// 벽은 통과할 수 없습니다.
// 세상 크기는 10*10
// 세상에는 플레이어와 몬스터와 목적지가 있다.
// 플레이어는 상하좌우로 이동 == 몬스터 동일
// 목적지에 플레이어가 도착하면 게임이 끝난다.

class Player
{
public:
	int x;
	int y;
	Player(int startX, int startY)
	{
		x = startX;
		y = startY;
	}

	void move(int dx, int dy, vector<vector<int>>& map)
	{

	}
};

class Monster
{
public:
	int x;
	int y;

	Monster(int startX, int startY)
	{
		x = startX;
		y = startY;
	}
};

class Map
{
public:


	Map(int rows, int cols, int initialTile = 0)
	{
		row = rows;
		col = cols;
		map = vector<vector<int>>(rows);
		for (int i = 0; i < rows; ++i) {
			map[i] = vector<int>(cols, initialTile);
		}
		makeMap();
	}

	void setPlayer(Player* p)
	{
		Mplayer = p;
	}
	void setMonster(Monster* m)
	{
		Mmonster = m;
	}

	void makeMap()
	{
		map = {
			{1,1,1,1,1,1,1,1,1,1},
			{1,0,1,0,0,0,1,0,0,1},
			{1,0,1,0,1,1,1,0,1,1},
			{1,0,1,0,0,0,1,0,0,1},
			{1,0,1,0,0,0,1,0,1,1},
			{1,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,1,1,1,1,1},
			{1,0,1,0,0,1,0,1,2,1},
			{1,0,1,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1}
		};
	}

	void moveMap(int x, int y)
	{
		int directions[4][2] = {
		   {-1, 0}, // 상
		   {1, 0},  // 하
		   {0, -1}, // 좌
		   {0, 1}   // 우
		};
	}

	void disPlay()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (Mplayer && i == Mplayer->x && j == Mplayer->y)
				{
					cout << "P";
				}
				else if (Mmonster && i == Mmonster->x && j == Mmonster->y)
				{
					cout << "M";
				}
				else
				{
					cout << map[i][j] << " ";
				}
			}
			cout << endl;
		}
	}


private:
	int row;
	int col;
	vector<vector<int>> map;
	Player* Mplayer = nullptr;
	Monster* Mmonster = nullptr;
};

int main()
{
	int n;
	cin >> n;

	Player player(1, 1);
	Monster monster(1, 8);
	Map map(n, n);
	map.setPlayer(&player);
	map.setMonster(&monster);


	map.disPlay();
	map.moveMap(0, 0);

	return 0;
}