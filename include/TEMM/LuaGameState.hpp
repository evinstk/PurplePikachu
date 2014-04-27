#ifndef LUA_GAME_STATE_HPP
#define LUA_GAME_STATE_HPP

#include <TEMM/State.hpp>

struct lua_State;

namespace temm
{
	//static int setUpdateBool(lua_State* luaState);

	class LuaGameState : public State
	{
	public:
		LuaGameState(StateStack& stack, Context context);
		~LuaGameState();

		void load(const std::string& filename);

		// Methods exposed to Lua
		static int setUpdateBool(lua_State* luaState);
		static int setHandleBool(lua_State* luaState);

		void draw();
		bool update(sf::Time dt);
		bool handleEvent(const sf::Event& event);
	private:
		unsigned mRegistryIndex;
		lua_State* mLuaState;

		bool mUpdate;
		bool mHandleEvent;

		static std::vector<LuaGameState*> LuaStateRegistry;
	};
}

#endif
