#pragma once
#include <vector>
#include "SDL.h"

class AActor;

class Engine
{
private:
	Engine();

public:
	void Init();
	void Term();

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


	struct SDL_Window* MyWindow;
	struct SDL_Renderer* MyRenderer;
	SDL_Event MyEvent;

};

#define GEngine			Engine::GetInstance()

