#include <iostream>
using namespace std;

int main()
{
	int a = 0;
	bool res = a < 10000;
	if (res)
	{

	}

	a = a + 1; // == a++ == a += 1

	for (int i = 0; i < 10000; i++)
	{
		cout << "i = " << i << endl;
	}

	return 0;
}