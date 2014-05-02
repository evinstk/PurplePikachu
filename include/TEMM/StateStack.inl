#include <TEMM/LuaState.hpp>

namespace temm
{
	template<typename T>
	void StateStack::registerState(States::ID stateID)
	{
		mFactories[stateID] = [this](bool luaWrapped)
		{
			return luaWrapped ? State::Ptr(new LuaState<T>(*this, mContext))
				: State::Ptr(new T(*this, mContext));
		};
	}
}
