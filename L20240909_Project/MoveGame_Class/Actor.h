#pragma once
class AActor
{
public:
	AActor()
	{
		X = 10;
		Y = 10;
	}

	virtual ~AActor()
	{

	}

	virtual void Tick(int KeyCode);
	void Render();

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


protected:
	int X;
	int Y;
	char StaticMesh;
};