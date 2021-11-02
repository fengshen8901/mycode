#include "FactorTest.h"
#include "head.h"

void FactorTest::Test()
{
	Factor fct;
	Produc* p = fct.CreatProduc(Factor::A1);
	Produc* p1 = fct.CreatProduc(Factor::A2);

	p->Display();
	p1->Display();

	delete p;
	delete p1;
}
