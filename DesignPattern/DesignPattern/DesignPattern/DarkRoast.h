#pragma once
#include "Beverage.h"
class DarkRoast :
    public Beverage
{
public:
    DarkRoast();
    double Cost() override;
};

