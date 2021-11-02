#pragma once
#include <array>

class Commond;
using sharedCommond = std::shared_ptr<Commond>;
class CommondControl
{
public:
	CommondControl();
	~CommondControl();
	void SetCommond(int slot, sharedCommond o, sharedCommond f);
	void ButtonDown(int slot);
	void ButtonUndoDown(int slot);

private:
	static const int maxSlot = 7;
	std::array<sharedCommond, maxSlot> commondons;
	std::array<sharedCommond, maxSlot> commondoffs;
	
};

