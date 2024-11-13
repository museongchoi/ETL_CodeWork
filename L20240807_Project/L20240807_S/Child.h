#pragma once
#include "Parent.h"

class Child : public Parent
{
public:
	Child();
	~Child();

	virtual void Investment() override;
};

