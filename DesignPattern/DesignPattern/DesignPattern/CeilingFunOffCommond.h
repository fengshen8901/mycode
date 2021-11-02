#pragma once
#include "Commond.h"
#include <memory>
#include "CeilingFan.h"

class CeilingFunOffCommond :
	public Commond
{
public:
	CeilingFunOffCommond(std::shared_ptr<CeilingFan> p);
	virtual void execute() override;
	virtual void undo() override;

private:
	std::shared_ptr<CeilingFan> ceilingFan;
	CeilingFan::SpeedType speed;
};