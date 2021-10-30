#include "Observer.h"
#include "Subject.h"

Observer::Observer()
{
	sub = nullptr;
}

Observer::Observer(Subject* s)
{
	sub = nullptr;
	if (s)
	{
		sub = s;
		s->Register(this);
	}
}

void Observer::Cancel()
{
	if (sub)
	{
		sub->Remove(this);
	}
	sub = nullptr;
}
