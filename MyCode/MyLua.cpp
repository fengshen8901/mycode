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
	lua_pop(luaState, top);	// ��ջ

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

	lua_getglobal(L, "val");
	int val = lua_tonumber(L, -1);
	std::cout << "val = " << val << std::endl; //tbl:name = shun  

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

void MyLua::LuaTest2()
{

}
