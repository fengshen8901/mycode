#include "ClassSize.h"
#include <iostream>

using namespace std;

void ClassSize::Test()
{
	cout << sizeof(cBase2) << endl;
	cout << sizeof(bDerived) << endl;
	cout << sizeof(bDerived1) << endl;
	cout << sizeof(bDerived2) << endl;
}
