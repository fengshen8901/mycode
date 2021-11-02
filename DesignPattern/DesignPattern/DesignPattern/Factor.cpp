#include "Factor.h"
#include "head.h"

Produc * Factor::CreatProduc(PuodctType t)
{
	switch (t)
	{
	case A1:
		return new ProducA1("A1");
		break;
	case A2:
		return new ProducA2("A2");
		break;
	case B1:
		return new ProducB1("B1");
		break;
	case B2:
		return new ProducB2("B2");
		break;
	default:
		break;
	}
	return nullptr;
}
