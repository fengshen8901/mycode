#include "Subject.h"
#include "Observer.h"
#include <iostream>


void Subject::Register(Observer* o)
{
	if (!o) return;
	obs.push_back(o);
}

void Subject::Remove(Observer* o)
{
	if (!o) return;
	obs.remove(o);
}

void Subject::Notify()
{
	for (auto o : obs)
	{
		o->Update();
	}
}