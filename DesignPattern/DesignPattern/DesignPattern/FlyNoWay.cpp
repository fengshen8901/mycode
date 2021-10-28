#include "FlyNoWay.h"
#include <iostream>

void FlyNoWay::Fly()
{
	std::cout << "fly no way" << std::endl;
}

FlyBehavlor* FlyNoWay::Clone()
{
	return new FlyNoWay;
}