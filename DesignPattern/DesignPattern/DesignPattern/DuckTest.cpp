#include "DuckTest.h"
#include "RedHeadDuck.h"
#include "GreenHeadDuck.h"
#include "FlyHigh.h"
#include "FlyNoWay.h"
#include "QuackG.h"
#include "QuackJ.h"
#include "QuackMute.h"

void DuckTest::Test()
{
	RedHeadDuck* duck = new RedHeadDuck;
	duck->Swim();
	duck->Display();
	duck->Fly();
	duck->Quack();

	FlyBehavlor* fly = new FlyHigh;
	QuackBehavlor* quack = new QuackG;
	duck->SetFly(fly);
	duck->SetQuack(quack);

	duck->Fly();
	duck->Quack();

	RedHeadDuck* duck1 = new RedHeadDuck(*duck);
	duck1->Fly();
	delete duck;
	delete duck1;
}
