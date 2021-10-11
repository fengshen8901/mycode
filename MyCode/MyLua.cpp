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

	//3.����Lua�ļ�  
	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet)
	{
		std::cout << "pcall error" << std::endl;
		return;
	}

	//4.��ȡ����  
	lua_getglobal(L, "str");
	std::string str = lua_tostring(L, -1);
	std::cout << "str = " << str.c_str() << std::endl;        //str = I am so cool~  

	//5.��ȡtable  
	lua_getglobal(L, "tbl");
	lua_getfield(L, -1, "name");
	str = lua_tostring(L, -1);
	std::cout << "tbl:name = " << str.c_str() << std::endl; //tbl:name = shun  

	//6.��ȡ����  
	lua_getglobal(L, "add");        // ��ȡ������ѹ��ջ��  
	lua_pushnumber(L, 10);          // ѹ���һ������  
	lua_pushnumber(L, 20);          // ѹ��ڶ�������  
	int iRet = lua_pcall(L, 2, 1, 0);// ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  
	if (iRet)                       // ���ó���  
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		std::cout << pErrorMsg << std::endl;
		lua_close(L);
		return;
	}
	if (lua_isnumber(L, -1))        //ȡֵ���  
	{
		double fValue = lua_tonumber(L, -1);
		std::cout << "Result is " << fValue << std::endl;
	}

	//7.�ر�state  
	lua_close(L);
	return;

	/*��Ҫע����ǣ���ջ�����ǻ���ջ���ģ�����˵��ֻ��ȥ����ջ����ֵ��
	�ٸ��Ƚϼ򵥵����ӣ����������������Ƚ�������ջ��������ջ��Ȼ����lua_pcall���ú�������ʱջ��Ϊ������ջ��Ϊ����������ջ���̴��»��ǣ�������ջ->�������->������ջ->�������->������ջ->���ú���->���ؽ����ջ��
	���ƵĻ���lua_setfield������һ�����ֵ���϶�Ҫ�Ƚ�ֵ��ջ�����棬��ȥ�ұ��λ�á�*/
}
