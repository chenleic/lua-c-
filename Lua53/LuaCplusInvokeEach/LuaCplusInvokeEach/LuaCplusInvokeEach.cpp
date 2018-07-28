// LuaCplusInvokeEach.cpp : �������̨Ӧ�ó������ڵ㡣
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

		//��֪key�������
		lua_getfield(l, 1, "chenl");
		if (lua_isstring(l, -1))
		{
			cout << lua_tostring(l, -1) << endl;
		}
		n = lua_gettop(l);
		lua_pop(l, 1);
		n = lua_gettop(l);



		//δ֪key�������
		lua_pushnil(l);
		while (lua_next(l, 1))
		{
			n = lua_gettop(l);
			printf("%s:%s - %s:%s\n",
				lua_typename(l, lua_type(l, -2)), lua_tostring(l, -2),
				lua_typename(l, lua_type(l, -1)), lua_tostring(l, -1));
			/* �Ƴ� 'value' ������ 'key' ����һ�ε��� */
			n = lua_gettop(l);
			lua_pop(l, 1);
			n = lua_gettop(l);
		}
	}
	lua_close(l);
}

//���Ե���lua�ļ��е�
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

	lua_getglobal(l, "add");  //��ȡadd function 
	lua_pushnumber(l, 1);     //ѹ���һ������
	lua_pushnumber(l, 2);     //ѹ��ڶ�������
	int n = lua_gettop(l);

	lua_pcall(l, 2, 3, NULL); //ִ��add function , ��θ���2�� ����ֵ����3
	n = lua_gettop(l);
	cout << lua_tonumber(l, -1) << endl;// ����������ֵ
	cout << lua_tonumber(l, -2) << endl;// �ڶ�������ֵ
	cout << lua_tonumber(l, -3) << endl;// ��һ������ֵ

	lua_close(l);
}



//lua����c++����

//���庯��
static int my_add(lua_State *L) {

	int a = lua_tonumber(L, -1);
	int b = lua_tonumber(L, -2);

	lua_pushnumber(L, a+b);
	return 1; //����һ������
}

//�������ֽӿڵ����飬 {NULL, NULL}����ȱ��
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

