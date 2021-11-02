#include "CeilingFunHighCommond.h"

CeilingFunHighCommond::CeilingFunHighCommond(std::shared_ptr<CeilingFan> p)
{
	ceilingFan = p;
	speed = CeilingFan::Off;
}

void CeilingFunHighCommond::execute()
{
	if (ceilingFan)
	{
		speed = ceilingFan->GetSpeed();
		ceilingFan->Run();
		ceilingFan->SetSpeed(CeilingFan::High);
	}
}

void CeilingFunHighCommond::undo()
{
	if (ceilingFan)
	{
		ceilingFan->SetSpeed(CeilingFan::High);
	}
}
