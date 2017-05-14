#pragma once
#include <lua.hpp>
#include <lualib.h>
#include <conio.h>

class LuaHandler
{
private:
	lua_State* L;
	char* inputStr;
	int counter = 0;

public:
	LuaHandler();
	void Update();
};