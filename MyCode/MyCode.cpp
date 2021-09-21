#include <iostream>
#include <set>
#include "Tool.h"
#include "MyString.h"
#include "STLalgorithm.h"
#include "MyTree.h"
#include "RBTree.h"
#include <forward_list>
#include<vector>
#include<map>
#include"ClassSize.h"

using namespace Tool;

class base
{
public:
	virtual void a() = 0;
};

int main()
{
	int val = 0x12345678;
	cout << hex;
	char* p = (char*)&val;
	for (int i = 0; i < 4; ++i)
	{
		cout << (int)p[i] << endl;
	}
	if (p[0] == 0x78)
	{
		cout << "small" << endl;
	}
	else
	{
		cout << "big" << endl;
	}
	
	////////////////////////////////////////////////////////
	system("pause");
	return 0;
}

