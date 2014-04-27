#include <TEMM/LuaGameState.hpp>
#include <lua.hpp>

namespace temm
{
	std::vector<LuaGameState*> LuaGameState::LuaStateRegistry(0);

	LuaGameState::LuaGameState(StateStack& stack, Context context)
		: State(stack, context)
		, mRegistryIndex(LuaStateRegistry.size())
		, mLuaState(luaL_newstate())
		, mUpdate(false)
		, mHandleEvent(false)
	{
		luaL_openlibs(mLuaState);
		LuaStateRegistry.push_back(this);
		lua_pushnumber(mLuaState, mRegistryIndex);
		lua_setglobal(mLuaState, "registryIndex");
		lua_pushcfunction(mLuaState, setUpdateBool);
		lua_setglobal(mLuaState, "setUpdateBool");
	}

	LuaGameState::~LuaGameState()
	{
		lua_close(mLuaState);
	}

	void LuaGameState::load(const std::string& filename)
	{
		if (std::strcmp(filename.c_str(), "") == 0) return;
		if (luaL_loadfile(mLuaState, filename.c_str()) || lua_pcall(mLuaState, 0, 0, 0))
		{
			throw std::runtime_error("LuaGameState::load - Failed to load " + filename);
		}
	}

	int LuaGameState::setUpdateBool(lua_State* luaState)
	{
		lua_getglobal(luaState, "registryIndex");
		int index = (int)luaL_checknumber(luaState, -1);
		bool updateBool = lua_toboolean(luaState, 1);
		LuaGameState::LuaStateRegistry[index]->mUpdate = updateBool;
		return 0;
	}

	void LuaGameState::draw()
	{
	}

	bool LuaGameState::update(sf::Time dt)
	{
		return mUpdate;
	}

	bool LuaGameState::handleEvent(const sf::Event& event)
	{
		return mHandleEvent;
	}

}
