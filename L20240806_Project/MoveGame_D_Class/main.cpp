#include <iostream> // include : 해당 파일을 복사 붙이기
#include "Player.h"
#include "Engine.h"

int main()
{
	UEngine* MyEngine = new UEngine;

	MyEngine->OpenLevel();

	delete MyEngine;

	return 0;
}



//{
//	APlayer Player1
//}
//Player1; //  오류 발생

//APlayer Player; // 컴파일 할때부터 메모리가 잡히고 들어간다.
//APlayer* PPlayer; // 플레이어가 만들어지면 메모리가 잡힌다.
//APlayer* PPlayer = new APlayer; // 컴파일 시간에 알 수 없는 데이터나 객체를 생성할 떄 유용하다.