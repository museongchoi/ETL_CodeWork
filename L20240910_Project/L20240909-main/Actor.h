#pragma once

#include "SDL.h"

enum class EDepth
{
	Background = 0,
	Floor = 5,
	Actor = 10,
	UI = 20,
	GameSystem = 1000,
	Max
};

enum class ECollisionType
{
	NoCollision = 0,
	Collision = 1,
	Overlap = 2,
	Max
};

class AActor
{
public:
	AActor();

	virtual ~AActor();

	virtual void Tick(int KeyCode);
	virtual void Render();
	virtual void BeginPlay();

	//acessor
	inline int GetX()
	{
		return X;
	}

	void SetX(int NewX)
	{
		X = NewX;
	}

	inline int GetY()
	{
		return Y;
	}

	void SetY(int NewY)
	{
		Y = NewY;
	}

	inline char GetStaticMesh()
	{
		return StaticMesh;
	}

	void SetStaticMesh(char	NewStaticMesh)
	{
		StaticMesh = NewStaticMesh;
	}

	EDepth GetDepth()
	{
		return Depth;
	}

	static bool Compare(AActor* A, AActor* B)
	{
		return (int)A->GetDepth() < (int)B->GetDepth();
	}

	ECollisionType CollisionType;

	bool PredictCollision(int NewX, int NewY);
	
	SDL_Color Color;

protected:
	int X;
	int Y;
	char StaticMesh;
	EDepth Depth;

	int SizeX;
	int SizeY;

	struct SDL_Surface* Surface;
	struct SDL_Texture* Texture;

};


