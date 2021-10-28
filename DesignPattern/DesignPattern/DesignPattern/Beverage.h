#pragma once
#include <string>
#include <iostream>
class Beverage
{
	friend class CondimentDecorator;
public:
	Beverage() :description("")
	{

	}

	virtual void GetDescription()
	{
		std::cout << description << std::endl;
	}
	virtual double Cost() = 0;
protected:
	std::string description;
};

