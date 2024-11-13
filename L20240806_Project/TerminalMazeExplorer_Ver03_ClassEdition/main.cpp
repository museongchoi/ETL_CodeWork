#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Image
{
public:
	int Idx;
	int X;
	int Y;
	int R;
	int G;
	int B;

};

class State
{
public:
	State() {}
	State(int newID, string newStateName)
	{
		ID = newID;
		StateName = newStateName;
	}
	int ID;
	string StateName;

};

class Transition
{
public:
	Transition() {}
	Transition(int newCurrentstatus, string newCindition, int newnextState)
	{
		currentstatus = newCurrentstatus;
		condition = newCindition;
		nextState = newnextState;
	}
	int currentstatus;
	string condition;
	int nextState;

};

int main()
{

	//Image* Images = new Image[100];
	vector<Image> Images;
	map<int, State> States;
	States[1] = State(1, "배회");
	States[2] = State(1, "추격");
	States[3] = State(1, "공격");
	States[4] = State(1, "죽음");

	map<string, Transition> Transitions;
	Transitions["적발견"] = Transition(1, "적발견", 2);
	Transitions["적놓침"] = Transition(2, "적놓침", 1);
	Transitions["사정거리접근"] = Transition(2, "사정거리접근", 3);
	Transitions["사정거리이탈"] = Transition(3, "사정거리이탈", 2);
	Transitions["HP없음"] = Transition(1, "HP없음", 2);

	int CurrentState = 1;
	Transition FindTransitions = Transitions["적발견"];
	int NextState = FindTransitions.nextState;


	//delete[] Images;

	return 0;
}