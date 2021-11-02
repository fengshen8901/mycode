#pragma once
#include "Commond.h"
#include <memory>
#include "CeilingFan.h"

class CeilingFunHighCommond :
	public Commond
{
public:
	CeilingFunHighCommond(std::shared_ptr<CeilingFan> p);
	virtual void execute() override;
	virtual void undo() override;

private:
	std::shared_ptr<CeilingFan> ceilingFan;
	CeilingFan::SpeedType speed;
};

