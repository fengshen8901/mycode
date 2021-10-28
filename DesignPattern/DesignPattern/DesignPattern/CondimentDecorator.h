#pragma once
#include "Beverage.h"
class CondimentDecorator :
    public Beverage
{
public:
    CondimentDecorator() :p(nullptr)
    {

    }

    ~CondimentDecorator()
    {
        if (p)
            delete p;
        p = nullptr;
    }

    CondimentDecorator(Beverage* o)
    {
        p = o;
        description = o->description;
    }

protected:
    Beverage* p;
};

