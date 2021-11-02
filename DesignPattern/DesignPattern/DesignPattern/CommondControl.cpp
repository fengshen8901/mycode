#include "CommondControl.h"
#include "NoCommond.h"

CommondControl::CommondControl()
{
	commondons.fill(std::make_shared<NoCommond>());
	commondoffs.fill(std::make_shared<NoCommond>());
}

CommondControl::~CommondControl()
{

}

void CommondControl::SetCommond(int slot, sharedCommond o, sharedCommond f)
{
	if (slot < 0 || maxSlot <= slot) return;
	commondons[slot] = o;
	commondoffs[slot] = f;
}

void CommondControl::ButtonDown(int slot)
{
	if (slot < 0 || maxSlot <= slot) return;
	commondons[slot]->execute();
}

void CommondControl::ButtonUndoDown(int slot)
{
	if (slot < 0 || maxSlot <= slot) return;
	commondoffs[slot]->undo();
}

