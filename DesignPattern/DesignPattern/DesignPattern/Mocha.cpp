#include "Mocha.h"

void Mocha::GetDescription()
{
    std::cout << "Mocha: ";
	if (p)
		p->GetDescription();
}

double Mocha::Cost()
{
	double cost = 0.1;
	if (p)
		cost += p->Cost();
	return cost;
}
