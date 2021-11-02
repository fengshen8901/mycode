#include "CeilingFunOffCommond.h"

CeilingFunOffCommond::CeilingFunOffCommond(std::shared_ptr<CeilingFan> p)
{
	ceilingFan = p;
	speed = CeilingFan::Off;
}

void CeilingFunOffCommond::execute()
{
	if (ceilingFan)
	{
		speed = ceilingFan->GetSpeed();
		ceilingFan->Stop();
	}
}

void CeilingFunOffCommond::undo()
{
	if (ceilingFan)
	{
		ceilingFan->SetSpeed(speed);
	}
}
