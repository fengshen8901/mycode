#include "ObserverTest.h"
#include "ConcreteSub.h"
#include "ConcreteObs.h"
#include <iostream>

void ObserverTest::Test()
{
	ConcreteSub* pS = new ConcreteSub;

	ConcreteObs* pO1 = new ConcreteObs("observer1", pS);
	ConcreteObs* pO2 = new ConcreteObs(pS);

	pS->Notify();

	pO2->Cancel();
	pS->Notify();

	delete pO2;
	delete pO1;
	delete pS;
}
