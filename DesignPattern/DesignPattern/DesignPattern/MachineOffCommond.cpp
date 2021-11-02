#include "MachineOffCommond.h"
#include "Machine.h"

MachineOffCommond::MachineOffCommond(std::shared_ptr<Machine> p)
{
	machine = p;
}

void MachineOffCommond::execute()
{
	if (machine)
	{
		machine->Down();
	}
}

void MachineOffCommond::undo()
{
	if (machine)
	{
		machine->Run();
	}
}
