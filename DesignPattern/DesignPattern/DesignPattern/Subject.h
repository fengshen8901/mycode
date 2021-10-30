#pragma once
#include <list>

class Observer;
class Subject
{
public:
	virtual void Register(Observer* o);
	virtual void Remove(Observer* o);
	virtual void Notify();

private:
	std::list<Observer*> obs;
};

