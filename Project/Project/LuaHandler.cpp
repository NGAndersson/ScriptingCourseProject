#include "LuaHandler.h"
#include <iostream>



LuaHandler::LuaHandler()
{
	L = luaL_newstate();
	luaL_openlibs(L);
	inputStr = new char[500];
	memset(inputStr, '\0', 500);
	//non-blocking input setup
}

void LuaHandler::Update()
{
	//Do String (Blocks when typing. Will use select() in linux later.) 
	if (_kbhit())
	{
		std::cin >> inputStr;

		int error = luaL_dostring(L, inputStr);
		if (error)
		{
			std::cout << "ERROR! Code failed to execute with message: " << lua_tostring(L, -1) << std::endl;
		}
		memset(inputStr, '\0', 500);
	}
}

