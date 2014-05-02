#ifndef LUA_GAME_STATE_HPP
#define LUA_GAME_STATE_HPP

#include <TEMM/State.hpp>
#include <memory>

struct lua_State;

namespace temm
{
	template <typename DerivedState>
	class LuaState : public State
	{
	public:
		LuaState(StateStack& stack, Context context);

		void load(const std::string& filename);

		void draw();
		bool update(sf::Time dt);
		bool handleEvent(const sf::Event& event);

	private:
		struct InterfaceSuite;

		void exposeInterface();

		unsigned mRegistryIndex;
		std::unique_ptr<lua_State, void(*)(lua_State*)> mLuaState;
		std::unique_ptr<DerivedState> mWrappedState;

		static std::vector<LuaState*> LuaStateRegistry;
	};
}

#include <TEMM/LuaState.inl>
#endif
