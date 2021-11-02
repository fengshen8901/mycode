#include "MyLua.h"
#include <iostream>



MyLua::MyLua()
{
	luaState = luaL_newstate();
	if (luaState)
	{
		luaopen_base(luaState);
	}
	else //print err
	{	}
}

MyLua::~MyLua()
{
	if (luaState)
	{
		lua_close(luaState);
		luaState = nullptr;
	}
}

bool MyLua::LoadLuaFile(const char* fileName)
{
	if (!luaState) return false; //print err
	auto err = luaL_dofile(luaState, fileName);
	if (err)
	{
		printf("[MyLua::LoadLuaFile]luaL_dofile(%s) is error(%d)(%s).\n",
			fileName, err, lua_tostring(luaState, -1));
		return false;
	}
	return true;
}

double MyLua::CallFileFun(const char* funName, const char* format, ...)
{
	if (!luaState) return false; //print err

	auto top = lua_gettop(luaState);
	lua_pop(luaState, top);	// 清栈

	lua_getglobal(luaState, funName);
	va_list args;
	va_start(args, format);
	int cnt = ParseParameter(format, args);
	va_end(args);

	double res = 0.0;
	int err = lua_pcall(luaState, cnt, 1, 0);
	if (err)
	{
		printf("[CLuaFn::CallFileFun]call function(%s) error(%d).\n", funName, err);
		return res;
	}

	if (lua_isnumber(luaState, -1))
		res = lua_tonumber(luaState, -1);
	return res;
}

lua_State* MyLua::GetState()
{
	return luaState;
}

int MyLua::ParseParameter(const char* format, va_list& args)
{
	int cnt = 0;
	char* p = (char*)format;
	while (*p != '\0')
	{
		if (*p == '%')
		{
			++p;
			switch (*p)
			{
			case 'd':
				lua_pushnumber(luaState, va_arg(args, int));
				break;
			case 'f':
				lua_pushnumber(luaState, va_arg(args, double));
				break;
			case 's':
				lua_pushstring(luaState, va_arg(args, char*));
				break;
			case 'z':
				lua_pushlightuserdata(luaState, va_arg(args, void*));
				break;
			default:
				break;
			}
			++cnt;
		}
		++p;
	}
	return cnt;
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

	lua_getglobal(L, "val");
	int val = lua_tonumber(L, -1);
	std::cout << "val = " << val << std::endl; //tbl:name = shun  

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

void MyLua::LuaTest2()
{

}
