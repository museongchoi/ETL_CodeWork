#include <iostream>
using namespace std;

int main()
{
	float Number1 = 0.0f;
	float Number2 = 0.0f;
	cin >> Number1;
	cin >> Number2;

	if (Number1 >= 10) // == if (Number > 10 or Number == 10)
	{
		cout << "Orange" << endl;
		if (Number1 == 10)
			cout << "Puple" << endl;
		else
			cout << "Yellow" << endl;
	}
	else
		cout << "Red" << endl;

	bool foo1 = false;
	bool foo2 = false;

	bool a = Number1 > 10;
	bool b = Number2 > 10;
	foo1 = a && b;
	foo2 = a || b;
	


	return 0;
}