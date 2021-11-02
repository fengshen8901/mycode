#pragma once
#include "Commond.h"
#include <memory>

class Machine;
class MachineOnCommond :
	public Commond
{
public:
	MachineOnCommond(std::shared_ptr<Machine> p);
	void execute() override;
	void undo() override;
private:
	std::shared_ptr<Machine> machine;
};

