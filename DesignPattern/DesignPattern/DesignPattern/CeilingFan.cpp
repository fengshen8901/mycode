#include "CeilingFan.h"
#include <iostream>

void CeilingFan::SetSpeed(SpeedType t)
{
	speed = t;
	if (t == Off)
	{
		Stop();
		return;
	}
	
	std::cout << "CeilingFan speed " << speed << std::endl;
}

CeilingFan::SpeedType CeilingFan::GetSpeed()
{
	return speed;
}

void CeilingFan::Run()
{
	std::cout << "CeilingFan on" << std::endl;
}

void CeilingFan::Stop()
{
	std::cout << "CeilingFan off" << std::endl;
}
