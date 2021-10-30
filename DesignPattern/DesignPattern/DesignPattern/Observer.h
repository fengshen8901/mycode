#pragma once

class Subject;
class Observer
{
public:
	Observer();
	Observer(Subject* s);
	virtual void Update() = 0;
	virtual void Cancel();

private:
	Subject* sub;
};

