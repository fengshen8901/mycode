#pragma once
#include "CondimentDecorator.h"
class Milk :
    public CondimentDecorator
{
public:
	using CondimentDecorator::CondimentDecorator;
	void GetDescription() override;
	double Cost() override;
};

