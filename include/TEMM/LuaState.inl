#include <lua.hpp>
#include <cassert>

namespace temm
{
	template <typename DerivedState>
	std::vector<LuaState<DerivedState>*> LuaState<DerivedState>::LuaStateRegistry(0);

	template <typename DerivedState>
	LuaState<DerivedState>::LuaState(StateStack& stack, Context context)
		: State(stack, context)
		, mRegistryIndex(LuaStateRegistry.size())
		, mLuaState(luaL_newstate(), lua_close)
		, mWrappedState(new DerivedState(stack, context))
	{
		assert(dynamic_cast<State*>(mWrappedState.get()) != nullptr);
		luaL_openlibs(mLuaState.get());
		LuaStateRegistry.push_back(this);
		lua_pushnumber(mLuaState.get(), mRegistryIndex);
		lua_setglobal(mLuaState.get(), "registryIndex");
		exposeInterface();
	}

	template <typename DerivedState>
	void LuaState<DerivedState>::load(const std::string& filename)
	{
		if (std::strcmp(filename.c_str(), "") == 0) return;
		if (luaL_loadfile(mLuaState.get(), filename.c_str()) || lua_pcall(mLuaState.get(), 0, 0, 0))
		{
			throw std::runtime_error("LuaGameState::load - Failed to load " + filename);
		}
	}

	template<typename DerivedState>
	void LuaState<DerivedState>::draw()
	{
		mWrappedState->draw();
	}

	template<typename DerivedState>
	bool LuaState<DerivedState>::update(sf::Time dt)
	{
		return mWrappedState->update(dt);
	}

	template<typename DerivedState>
	bool LuaState<DerivedState>::handleEvent(const sf::Event& event)
	{
		return mWrappedState->handleEvent(event);
	}

	template<typename DerivedState>
	void LuaState<DerivedState>::exposeInterface()
	{
	}

}
