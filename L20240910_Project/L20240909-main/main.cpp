#include "SDL.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")


int SDL_main(int agrc, char* agrv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* MyWindow = SDL_CreateWindow("HelloWorld", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	//SDL_Renderer* MyRenderer =  SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	
	bool bIsRunning = true;
	SDL_Event MyEvent;
	int PlayerX = 400;
	int PlayerY = 400;

	while (bIsRunning)
	{
		SDL_PollEvent(&MyEvent);
		switch (MyEvent.type)
		{
		case SDL_QUIT:
			bIsRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (MyEvent.key.keysym.sym)
			{
			case SDLK_UP:
				PlayerY--;
				break;
			case SDLK_LEFT:
				PlayerX--;
				break;
			case SDLK_RIGHT:
				PlayerX++;
				break;
			case SDLK_DOWN:
				PlayerY++;
				break;
			}
			break;
		}
		
		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(MyRenderer);

		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0, 0, 0xff);
		SDL_RenderDrawPoint(MyRenderer, 100, 100);


		SDL_Rect MyRect = { PlayerX, PlayerY, 100, 100 };
		//SDL_Rect MyRect = { 100, 100, 100, 100 };
		//SDL_RenderDrawRect(MyRenderer, &MyRect); // 빈 네모
		SDL_RenderFillRect(MyRenderer, &MyRect);	// 색이 찬 네모

		double PI = 3.1415926;
		
		//for (int Redius = 1; Redius < 100; ++Redius)
		//{
		//	for (int i = 0; i <= 360; i++)
		//	{
		//		int X1 = SDL_cos(i * PI / 180.0f) * Redius;
		//		int Y1 = SDL_sin(i * PI / 180.0f) * Redius;;
		//		int X2 = SDL_cos((i + 10) * PI / 180.0f) * Redius;
		//		int Y2 = SDL_sin((i + 10) * PI / 180.0f) * Redius;
		//		SDL_RenderDrawLine(MyRenderer, PlayerX + X1, PlayerY + Y1, PlayerX + X2, PlayerY + Y2);
		//	}
		//}
		SDL_RenderPresent(MyRenderer);

		//double PI = 3.1415926;
		//for (int i = 0; i <= 360; i++)
		//{
		//	int X1 = SDL_cos(i * PI / 180.0f) * 100;
		//	int Y1 = SDL_sin(i * PI / 180.0f) * 100;;
		//	int X2 = SDL_cos((i + 10) * PI / 180.0f) * 100;
		//	int Y2 = SDL_sin((i + 10) * PI / 180.0f) * 100;
		//	SDL_RenderDrawLine(MyRenderer, 400 + X1, 400 + Y1, 400 + X2, 400 + Y2);

		//}
		//SDL_RenderPresent(MyRenderer);
	}

	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);

	SDL_Quit();
	return 0;
}

//#include "Engine.h"
//
//int main()
//{
//
//	GEngine->LoadLevel("Level01.Map");
//
//	GEngine->Run();
//
//	return 0;
//}