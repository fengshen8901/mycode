#include "FlyHigh.h"
#include <iostream>

void FlyHigh::Fly()
{
	std::cout << "fly high" << std::endl;
}

FlyBehavlor* FlyHigh::Clone()
{
	return new FlyHigh;
}
