#include <iostream>
using namespace std;

int main()
{
	//int a, b, c;
	/*int a = 0;
	int b = 0;
	int c = 0;*/
	int input[3];

	cout << "Enter the Integer values a,b,c : ";

	cin >> input[0] >> input[1] >> input[2];
	
	for (int element : input)
	{
		cout << element << endl;
	}

	return 0;
}