#pragma once
#include <WinSock2.h>


enum class ECommand
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
	Set = 4,
	Spawn = 100,
	Destroy = 101,
	PostLogin = 102,
};

unsigned short Length;

#pragma pack(push, 1)
typedef struct _packet
{
	unsigned short Code;
	SOCKET Id;
	unsigned short X;
	unsigned short Y;
	unsigned short R;
	unsigned short G;
	unsigned short B;
} Packet;

void MakeNetworkOrder(Packet& Data)
{
	Data.Code = htons(Data.Code);
	Data.Id = (SOCKET)htonll(Data.Id);
	Data.X = htons(Data.X);
	Data.Y = htons(Data.Y);
	Data.R = htons(Data.R);
	Data.G = htons(Data.G);
	Data.B = htons(Data.B);
}

void MakeHostOrder(Packet& Data)
{
	Data.Code = ntohs(Data.Code);
	Data.Id = (SOCKET)htonll(Data.Id);
	Data.X = ntohs(Data.X);
	Data.Y = ntohs(Data.Y);
	Data.R = ntohs(Data.R);
	Data.G = ntohs(Data.G);
	Data.B = ntohs(Data.B);
}
#pragma pack(pop)
