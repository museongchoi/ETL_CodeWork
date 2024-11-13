#pragma once

class UWorld;

class UEngine
{
public:
	UEngine();
	~UEngine();

	void OpenLevel();
	void Run();

	UWorld* World;
};

