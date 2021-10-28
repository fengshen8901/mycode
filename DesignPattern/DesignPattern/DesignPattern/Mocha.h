#pragma once
#include "CondimentDecorator.h"
class Mocha :
    public CondimentDecorator
{
public:
	using CondimentDecorator::CondimentDecorator;
	void GetDescription() override;
	double Cost() override;
};

