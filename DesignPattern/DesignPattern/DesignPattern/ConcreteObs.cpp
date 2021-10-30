#include "ConcreteObs.h"
#include <iostream>

ConcreteObs::ConcreteObs(const char* str, Subject* sub) :name(str), Observer(sub)
{

}

void ConcreteObs::Update()
{
	std::cout << name << " ConcreteObs Update" << std::endl;
}
