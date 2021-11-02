#include "MachineOnCommond.h"
#include "Machine.h"

MachineOnCommond::MachineOnCommond(std::shared_ptr<Machine> p)
{
	machine = p;
}

void MachineOnCommond::execute()
{
	if (machine)
	{
		machine->Run();
	}
}

void MachineOnCommond::undo()
{
	if (machine)
	{
		machine->Down();
	}
}
