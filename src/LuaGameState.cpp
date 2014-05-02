#include <TEMM/LuaState.hpp>
#include <TEMM/GameState.hpp>

namespace temm
{

	template <>
	struct LuaState<GameState>::InterfaceSuite
	{

		static int loadTMX(lua_State* luaState)
		{
			lua_getglobal(luaState, "registryIndex");
			int index = (int)luaL_checknumber(luaState, -1);
			std::string filename = luaL_checkstring(luaState, 1);
			GameState& state = *LuaState<GameState>::LuaStateRegistry[index]->mWrappedState.get();
			state.mOverworld.loadTMX(filename);
			return 0;
		}

	};

	template <>
	void LuaState<GameState>::exposeInterface()
	{
		lua_pushcfunction(mLuaState.get(), InterfaceSuite::loadTMX);
		lua_setglobal(mLuaState.get(), "loadTMX");
	}

}
