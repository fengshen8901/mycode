#include "Milk.h"

void Milk::GetDescription()
{
	std::cout << "milk: ";
	if (p)
		p->GetDescription();
}

double Milk::Cost()
{
	double cost = 0.2;
	if (p)
		cost += p->Cost();
	return cost;
}
