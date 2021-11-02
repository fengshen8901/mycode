#pragma once
#include "Commond.h"
#include <memory>
class Machine;
class MachineOffCommond :
	public Commond
{
public:
	MachineOffCommond(std::shared_ptr<Machine> p);
	void execute() override;
	void undo() override;
private:
	std::shared_ptr<Machine> machine; 
};

