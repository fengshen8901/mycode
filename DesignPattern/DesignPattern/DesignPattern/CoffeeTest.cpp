#include "CoffeeTest.h"
#include "DarkRoast.h"
#include "HouseBlend.h"
#include "Milk.h"
#include "Mocha.h"

void CoffeeTest::Test()
{
	Beverage* hb = new HouseBlend;
	hb->GetDescription();
	std::cout << "cost: " << hb->Cost() << std::endl;

	hb = new Milk(hb);
	hb->GetDescription();
	std::cout << "cost: " << hb->Cost() << std::endl;

	hb = new Mocha(hb);
	hb->GetDescription();
	std::cout << "cost: " << hb->Cost() << std::endl;

	delete hb;
}
