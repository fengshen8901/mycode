#include "MyLua.h"
#include <iostream>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lauxlib.h"
}

void MyLua::LuaTest()
{
	lua_State* L = luaL_newstate();

	lua_pushstring(L, "I am so cool~");
	lua_pushnumber(L, 20);

	if (lua_isstring(L, 1))
		std::cout << lua_tostring(L, 1) << std::endl;
	if (lua_isnumber(L, -1))
		std::cout << lua_tonumber(L, -1) << std::endl;

	lua_close(L);
}

void MyLua::LuaTest1()
{
	lua_State* L = luaL_newstate();
	if (!L) return;

	int bRet = luaL_loadfile(L, "..//lua//hello.lua");
	if (bRet)
	{
		std::cout << "load file error" << std::endl;
		return;
	}

	//3.运行Lua文件  
	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet)
	{
		std::cout << "pcall error" << std::endl;
		return;
	}

	//4.读取变量  
	lua_getglobal(L, "str");
	std::string str = lua_tostring(L, -1);
	std::cout << "str = " << str.c_str() << std::endl;        //str = I am so cool~  

	//5.读取table  
	lua_getglobal(L, "tbl");
	lua_getfield(L, -1, "name");
	str = lua_tostring(L, -1);
	std::cout << "tbl:name = " << str.c_str() << std::endl; //tbl:name = shun  

	//6.读取函数  
	lua_getglobal(L, "add");        // 获取函数，压入栈中  
	lua_pushnumber(L, 10);          // 压入第一个参数  
	lua_pushnumber(L, 20);          // 压入第二个参数  
	int iRet = lua_pcall(L, 2, 1, 0);// 调用函数，调用完成以后，会将返回值压入栈中，2表示参数个数，1表示返回结果个数。  
	if (iRet)                       // 调用出错  
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		std::cout << pErrorMsg << std::endl;
		lua_close(L);
		return;
	}
	if (lua_isnumber(L, -1))        //取值输出  
	{
		double fValue = lua_tonumber(L, -1);
		std::cout << "Result is " << fValue << std::endl;
	}

	//7.关闭state  
	lua_close(L);
	return;

	/*需要注意的是：堆栈操作是基于栈顶的，就是说它只会去操作栈顶的值。
	举个比较简单的例子，函数调用流程是先将函数入栈，参数入栈，然后用lua_pcall调用函数，此时栈顶为参数，栈底为函数，所以栈过程大致会是：参数出栈->保存参数->参数出栈->保存参数->函数出栈->调用函数->返回结果入栈。
	类似的还有lua_setfield，设置一个表的值，肯定要先将值出栈，保存，再去找表的位置。*/
}
