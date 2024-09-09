#include <iostream>	
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	// 1. 3.14 고정
	float pie = 3.14f;
	int circle;
	cin >> circle;

	float extent = pie * (float)circle * (float)circle;

	cout << extent << "\n";
	cout << "\n";

	// 2. 헤드 파일 선언
	cin >> circle;

	extent = M_PI * (float)circle * (float)circle;
	cout << extent << endl;

	// 3. pi 고정
	const double pi = 3.14159265358979;
	cout << (float)pi << "\n";

	cin >> circle;

	extent = pi * circle * circle;
	cout << extent << endl;

	// 4. 교수님
	float Radius = 0.0f;

	cin >> Radius;

	cout << Radius * Radius * 3.1415f << endl;

	return 0;
}