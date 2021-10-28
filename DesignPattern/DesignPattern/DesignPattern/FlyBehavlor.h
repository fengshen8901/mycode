#pragma once
class FlyBehavlor
{
public:
	virtual void Fly() = 0;
	virtual FlyBehavlor* Clone() = 0;
};

