#include "Produc.h"
#include <iostream>

Produc::Produc(const char * str)
{
	dis = str;
}

void Produc::Display()
{
	std::cout << dis << std::endl;
}
