#pragma once
#include <vadefs.h>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lauxlib.h"
#include "tolua++.h"
#include "lualib.h"
}

class MyLua
{
public:
	MyLua();
	~MyLua();
	bool LoadLuaFile(const char* fileName);
	double CallFileFun(const char* funName, const char* format, ...);
	lua_State* GetState();
	template<typename T>
	T GetVar(const char* varName)
	{
		if (!luaState) return 0;
		lua_getglobal(luaState, varName);
		if (lua_isnumber(luaState, -1))
			return lua_tonumber(luaState, -1);		
		return 0;
	}
	const char* GetVar(const char* varName)
	{
		if (!luaState) return "";
		lua_getglobal(luaState, varName);
		if (lua_isstring(luaState, -1))
			return lua_tostring(luaState, -1);
		return "";
	}

	static void LuaTest();
	static void LuaTest1();
	static void LuaTest2();

private:
	int ParseParameter(const char* format, va_list& args);

private:
	lua_State* luaState;
};

