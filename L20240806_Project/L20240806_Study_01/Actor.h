#pragma once
class AActor
{
public: // interface | 나랑 대면하다
	AActor();
	~AActor();

	void Move();


	// 접근을 하거나 세팅을 할 수 있게 하는 것.
	int GetHP() { return HP; }
	void SetHP(int NewHP) 
	{
		if (NewHP >= 0)
		{
			HP = NewHP;
		}
	}

private:
	//int HP;

protected:
	int HP;

};

//                         접근
//public                   아무대나 접근
//protected                내부
//private                  내부

