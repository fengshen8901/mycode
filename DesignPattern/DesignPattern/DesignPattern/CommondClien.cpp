#include "CommondClien.h"
#include "head.h"

void CommondClien::ClientRun()
{
	std::shared_ptr<CommondControl> control = std::make_shared<CommondControl>();

	std::shared_ptr<Machine> m = std::make_shared<Machine>();
	std::shared_ptr<Commond> cmdMOn(new MachineOnCommond(m));
	std::shared_ptr<Commond> cmdMOFF(new MachineOnCommond(m));

	std::shared_ptr<CeilingFan> c = std::make_shared<CeilingFan>();
	std::shared_ptr<Commond> cmdCHigh(new CeilingFunHighCommond(c));
	std::shared_ptr<Commond> cmdCOFF(new CeilingFunOffCommond(c));

	control->SetCommond(0, cmdMOn, cmdMOFF);
	control->SetCommond(2, cmdCHigh, cmdCOFF);

	control->ButtonDown(0);
	control->ButtonDown(1);
	control->ButtonDown(2);
	control->ButtonDown(3);

	control->ButtonUndoDown(0);
	control->ButtonUndoDown(1);
	control->ButtonUndoDown(2);
	control->ButtonUndoDown(3);
}
