#pragma once
class AActor
{
public: //interface
	AActor();
	~AActor();

	virtual void Move(); // virtual : 해당 함수는 자식이 재정의 할 수도 있다.

	int GetHP() { return HP; }
	void SetHP(int NewHP) 
	{
		if (NewHP >= 0)
		{
			HP = NewHP;
		}
	}
protected: 
//private:

	int HP;
};

//					접근					상속
//public			아무대나 접근			상속
//protected			내부					상속
//private			내부					상속X

