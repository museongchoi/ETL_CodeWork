#pragma once // 전처리 과정에서 한번 복사가되면 하지말라. | 한번만 복사하게 하는 것.
#include <iostream>

class Parent
{
public:
	Parent();
	~Parent();

	// 
	inline int GetMoney()
	{
		return Money;
	}

	void SetMoney(int NewMoney)
	{
		if (NewMoney > 0)
		{
			Money = NewMoney;
		}
	}

	virtual void Investment()
	{
		srand((unsigned int)(time (nullptr)));
		Money = (rand() % 2) == 1 ? Money * 2 : 0;

	}


	//int Money;

protected:
	int Money;
private:
	//int Money;
};


//namespace Choi // 한단계 더 큰 클래스 사용자 이름
//{
//	class Parent
//	{
//	public:
//		Parent();
//		~Parent();
//	};
//}
