#pragma once

#include <map>
#include <random>
#include <winsock2.h>

using namespace std;

class SessionInfo
{
public:
	SessionInfo()
	{
		random_device RandomDevice;
		mt19937 MT19937(RandomDevice());
		std::uniform_int_distribution<int> ColorDist(0, 255);
		std::uniform_int_distribution<int> XPositionDist(0, 80);
		std::uniform_int_distribution<int> YPositionDist(0, 25);

		X = XPositionDist(MT19937);
		Y = YPositionDist(MT19937);
		R = ColorDist(MT19937);
		G = ColorDist(MT19937);
		B = ColorDist(MT19937);
	}

	SessionInfo(unsigned short InX,
		unsigned short InY,
		unsigned short InR,
		unsigned short InG,
		unsigned short InB)
	{
		X = InX;
		Y = InY;
		R = InR;
		G = InG;
		B = InB;
	}


	~SessionInfo() {}

	unsigned short X;
	unsigned short Y;
	unsigned short R;
	unsigned short G;
	unsigned short B;
};

class Session
{
public:
	Session() {}
	~Session() {}

	map<SOCKET, SessionInfo> List;

	void Insert(SOCKET ID, SessionInfo Info)
	{
		List[ID] = Info;
	}

	void Remove(SOCKET ID)
	{
		List.erase(List.find(ID));
	}
};