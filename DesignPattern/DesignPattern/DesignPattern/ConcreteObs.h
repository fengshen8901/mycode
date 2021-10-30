#pragma once
#include "Observer.h"
#include <string>
class ConcreteObs :
    public Observer
{
public:
    using Observer::Observer;
    ConcreteObs(const char* str, Subject* sub = nullptr); 

    void Update() override;

private:
    std::string name;
};

