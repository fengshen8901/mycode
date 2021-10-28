#pragma once
#include "FlyBehavlor.h"

class FlyHigh :
    public FlyBehavlor
{
public:
    void Fly() override;
    FlyBehavlor* Clone() override;
};

