#pragma once
#include <vector>

class AActor;

class Engine
{
public:
	Engine()
	{
		KeyCode = 0;
		bIsRunning = true;
	}

	virtual ~Engine()
	{

	}

protected:
	void Input();
	void Tick();
	void Render();
	//void Stop();

	std::vector<AActor*> Actors;
	int KeyCode;
	bool bIsRunning;

public:
	void Run();
	void SpawnActor(class AActor* SpawnedActor);

	
};