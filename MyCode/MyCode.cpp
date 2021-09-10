#include <iostream>
#include <set>
#include "Tool.h"
#include "MyString.h"
#include "STLalgorithm.h"
#include "MyTree.h"
#include "RBTree.h"
#include <forward_list>
#include<vector>

using namespace Tool;



int main()
{
	forward_list<int> lst;
	lst.emplace_after(lst.before_begin(), 4);
	////////////////////////////////////////////////////////
	system("pause");
	return 0;
}

