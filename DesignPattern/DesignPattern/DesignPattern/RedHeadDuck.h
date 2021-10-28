#pragma once
#include "Duck.h"

class RedHeadDuck: public Duck
{
	using Duck::Duck;
public:
	void Display() override;
};

