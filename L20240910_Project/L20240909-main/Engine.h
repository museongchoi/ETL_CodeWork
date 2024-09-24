#pragma once
#include <vector>

class AActor;

class Engine
{
private:
	Engine()
	{
		KeyCode = 0;
		bIsRunning = true;
		bWillStop = false;
	}

public:

	static Engine* GetInstance()
	{
		if (!Instance)
		{
			Instance = new Engine();
		}

		return Instance;
	}

	virtual ~Engine();

protected:
	void Input();
	void Tick();
	void Render();
	void BeginPlay();


	std::vector<AActor*> Actors;
	int KeyCode;
	bool bIsRunning;
	bool bWillStop;

	static Engine* Instance;

public:
	void Run();
	void SpawnActor(AActor* SpawnedActor);
	void LoadLevel(const char* MapName);

	// 참조자를 주지 않으면 해당 값들을 다 복사하여 준다. 화살표와 해당 값을 다 주는것. 즉, 화살표만 넘겨준다는 개념으로 참조자를 사용.
	//std::vector < AActor*> GetActors() 
	std::vector < AActor*>& GetActors()
	{
		return Actors;
	}
	void Stop()
	{
		bWillStop = true;
	}
};

#define GEngine			Engine::GetInstance()

