#pragma once
#include "FlyBehavlor.h"

class FlyNoWay :
    public FlyBehavlor
{
    void Fly() override;
    FlyBehavlor* Clone() override;
};

