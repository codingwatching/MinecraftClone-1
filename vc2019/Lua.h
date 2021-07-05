#pragma once
#include <string>

extern "C" {
#include "../lua 5.4.2/include/lua.h"
#include "../lua 5.4.2/include/lauxlib.h"
#include "../lua 5.4.2/include/lualib.h"
}
#pragma comment(lib,"../lua 5.4.2/liblua54.a")
#include<stdarg.h>

class LUA {
	lua_State* L;
public:
	LUA() {
		L = luaL_newstate();
		luaL_openlibs(L);
	}
	~LUA()
	{
		lua_close(L);
	}

	lua_State* GetLuaState() {
		return L;
	}

	void LoadFunct(std::string name) {
		lua_getglobal(L, name.c_str());
	}

	//void

	//typedef int (*LuaCompatFunct)(lua_State* L);


	//void AddFunctToLua(LuaCompatFunct funct,std::string name) {
	//	lua_register(L, name.c_str(), funct);
	//}

	//template <typename T>
	//void AddFunctToLua(LuaCompatFunct funct, std::string name) {
	//	lua_register(L, name.c_str(), funct);
	//}

	//template <typename T>
	//T ExecuteString(std::string s) {
	//	int r = luaL_dostring(L, s.c_str());
	//	if (r == LUA_OK) {
	//		//lua_getglobal(L,)
	//	}
	//	else {
	//		std::string err = lua_tostring(L, -1);
	//	}
	//}

	//

	//void ExecuteFile(std::string s) {

	//}

};
