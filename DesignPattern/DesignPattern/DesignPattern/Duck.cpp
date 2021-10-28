#include "Duck.h"
#include <iostream>
#include "FlyBehavlor.h"
#include "QuackBehavlor.h"

#define SAFE_DEL(p) if(p) delete p; p = nullptr; 

Duck::Duck():fly(nullptr), quack(nullptr)
{

}

Duck::~Duck()
{
	SAFE_DEL(fly);
	SAFE_DEL(quack);
}

Duck::Duck(const Duck& d)
{
	std::cout << "duck copy construct" << std::endl;
	fly = d.fly->Clone();
	quack = nullptr;
}

Duck::Duck(Duck&& d) noexcept
{
	std::cout << "duck move construct" << std::endl;
	fly = d.fly;
	d.fly = nullptr;
	quack = d.quack;
	d.quack = nullptr;
}

Duck& Duck::operator=(const Duck& d)
{
	std::cout << "duck copy =" << std::endl;
	fly = d.fly->Clone();
	quack = nullptr;
	return *this;
}

Duck& Duck::operator=(Duck&& d) noexcept
{
	std::cout << "duck move =" << std::endl;
	fly = d.fly;
	d.fly = nullptr;
	quack = d.quack;
	d.quack = nullptr;
	return *this;
}

void Duck::Swim()
{
	std::cout << "duck swim" << std::endl;
}

void Duck::Display()
{
	std::cout << "base duck" << std::endl;
}

void Duck::Quack()
{
	if (quack)
		quack->Quack();
	else
		std::cout << "unknown quack" << std::endl;
}

void Duck::Fly()
{
	if (fly)
		fly->Fly();
	else
		std::cout << "unknown fly" << std::endl;
}

void Duck::SetFly(FlyBehavlor* f)
{
	SAFE_DEL(fly);
	fly = f;
}

void Duck::SetQuack(QuackBehavlor* q)
{
	SAFE_DEL(quack);
	quack = q;
}