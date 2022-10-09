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
#include "MyLua.h"

using namespace Tool;

class base
{
public:
	virtual void a() = 0;
};
int tolua_MyCode_open(lua_State* tolua_S);

struct stBitArea
{
	stBitArea() : adulp(0), planInterruptionDays(0)
	{

	}

	short adulp : 8;
	short planInterruptionDays : 8;
};

int main()
{
	

	//const char* p = "&actor=%E9%98%BF%E6%96%AF%E8%92%82%E6%9C%89&actor_id";
	//std::cout << p << std::endl;
	//std::cout << strlen(p) << std::endl;


	//ClassSize::Test();

	//MyLua::LuaTest1();

	//MyLua la;
	//tolua_MyCode_open(la.GetState());
	//la.LoadLuaFile("..//lua//hello.lua");

	//auto res = la.CallFileFun("add", "%d%f", 3, 3.14);
	//std::cout << res << std::endl;

	//std::cout << la.GetVar("str") << std::endl;
	//std::cout << la.GetVar<int>("val") << std::endl;

	////读取table
	//auto L = la.GetState();
	//lua_getglobal(L, "tbl");
	//lua_getfield(L, -1, "name");
	//std::cout << lua_tostring(L, -1) << std::endl;
	////////////////////////////////////////////////////////
	system("pause");
	return 0;
}

