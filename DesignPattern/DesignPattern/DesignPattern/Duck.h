#pragma once

class FlyBehavlor;
class QuackBehavlor;

class Duck
{
public:
	Duck();
	~Duck();

	Duck(const Duck& d);
	Duck(Duck&& d) noexcept;
	Duck& operator=(const Duck& d);
	Duck& operator=(Duck&& d) noexcept;

	virtual void Swim();
	virtual void Display();
	virtual void Quack();
	virtual void Fly();

	virtual void SetFly(FlyBehavlor* f);
	virtual void SetQuack(QuackBehavlor* q);
private:
	FlyBehavlor* fly;
	QuackBehavlor* quack;
};

