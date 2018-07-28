// LuaCplusInvokeEach.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <lua.hpp>
#include <windows.h>
#include <iostream>

using namespace std;

void testLua1()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);


	lua_pushstring(l, "I am very cool.....");
	lua_pushnumber(l, 20);
	//lua_pop(l, 0);
	lua_settop(l, 1);
	int n = lua_gettop(l);

	if (lua_isstring(l, 1))
	{
		cout << lua_tostring(l, 1) << endl;
	}


	if (lua_isnumber(l, -1))
	{
		cout << lua_tonumber(l, -1) << endl;
	}

	lua_close(l);
}

//test lua table
void TestLua2()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);

	int n = lua_gettop(l);

	lua_newtable(l);

	lua_pushstring(l, "haha, gf");
	n = lua_gettop(l);
    lua_setfield(l, 1,"name");
	n = lua_gettop(l);

	if (lua_istable(l, -1))
	{
	//	lua_getfield(l, -2, "name");
		lua_pushstring(l, "chenl");
		lua_pushstring(l, "920701");
		n = lua_gettop(l);
		lua_settable(l, 1);
		n = lua_gettop(l);

		//已知key的情况下
		lua_getfield(l, 1, "chenl");
		if (lua_isstring(l, -1))
		{
			cout << lua_tostring(l, -1) << endl;
		}
		n = lua_gettop(l);
		lua_pop(l, 1);
		n = lua_gettop(l);



		//未知key的情况下
		lua_pushnil(l);
		while (lua_next(l, 1))
		{
			n = lua_gettop(l);
			printf("%s:%s - %s:%s\n",
				lua_typename(l, lua_type(l, -2)), lua_tostring(l, -2),
				lua_typename(l, lua_type(l, -1)), lua_tostring(l, -1));
			/* 移除 'value' ；保留 'key' 做下一次迭代 */
			n = lua_gettop(l);
			lua_pop(l, 1);
			n = lua_gettop(l);
		}
	}
	lua_close(l);
}

//测试调用lua文件中的
void testLua3()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);

	int nResult = luaL_loadfile(l, "test.lua");
	if (nResult)
	{
		cout << lua_tostring(l, -1) << endl;
		return;
	}

	nResult = lua_pcall(l, 0,0,0);
	if (nResult)
	{
		cout << lua_tostring(l, -1) << endl;
		return;
	}

	lua_getglobal(l, "add");  //获取add function 
	lua_pushnumber(l, 1);     //压入第一个参数
	lua_pushnumber(l, 2);     //压入第二个参数
	int n = lua_gettop(l);

	lua_pcall(l, 2, 3, NULL); //执行add function , 入参个数2， 返回值个数3
	n = lua_gettop(l);
	cout << lua_tonumber(l, -1) << endl;// 第三个返回值
	cout << lua_tonumber(l, -2) << endl;// 第二个返回值
	cout << lua_tonumber(l, -3) << endl;// 第一个返回值

	lua_close(l);
}



//lua调用c++函数

//定义函数
static int my_add(lua_State *L) {

	int a = lua_tonumber(L, -1);
	int b = lua_tonumber(L, -2);

	lua_pushnumber(L, a+b);
	return 1; //返回一个参数
}

//供绑定两种接口的数组， {NULL, NULL}不可缺少
static const luaL_Reg mylib[] = {
	{ "myadd", my_add },
	{ NULL, NULL }
};

int luaopen_mytestlib(lua_State *L)
{
	luaL_newlib(L, mylib);
	//luaL_register(L, "mytestlib", mylib);
	return 1;
}

void testLua4()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);

	lua_register(l, "myadd", my_add);
//	luaopen_mytestlib(l);

	int nResult = luaL_loadfile(l, "test.lua");
	if (nResult)
	{
		cout << lua_tostring(l, -1) << endl;
		return;
	}

	nResult = lua_pcall(l, 0, 0, 0);
	if (nResult)
	{
		cout << lua_tostring(l, -1) << endl;
		return;
	}
	
	lua_getglobal(l, "testmy");
	lua_pushnumber(l, 100);
	lua_pushnumber(l, 101);
	lua_pcall(l, 2, 1, NULL);

	int n = lua_gettop(l);
//	cout << n << endl;
	cout << lua_tonumber(l, -1) << endl;

	lua_close(l);
}

int _tmain(int argc, _TCHAR* argv[])
{
	testLua1();
	
	TestLua2();

	testLua3();

	testLua4();

	system("pause");
	return 0;
}

