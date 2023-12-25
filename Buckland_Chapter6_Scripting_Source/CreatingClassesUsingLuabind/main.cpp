// include the libraries
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>
#include <iostream>
using namespace std;

// include the luabind headers. Make sure you have the paths set correctly
// to the lua, luabind and Boost files.
#include <luabind/luabind.hpp>
using namespace luabind;

#include "lua/LuaHelperFunctions.h"

int main()
{
    // create a lua state
    lua_State *pLua = lua_open();

    // open the lua libaries - new in lua5.1
    luaL_openlibs(pLua);

    // open luabind
    open(pLua);

    // load and run the script
    RunLuaScript(pLua, "classes_in_lua.lua");

    lua_close(pLua);

    return 0;
}
