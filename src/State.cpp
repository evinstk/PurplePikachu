#include <TEMM/State.hpp>
#include <TEMM/StateStack.hpp>

namespace temm
{
	State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, KeyBinding& keys1)
		: window(&window)
		, textures(&textures)
		, keys1(&keys1)
	{
	}

	State::State(StateStack& stack, Context context)
		: mStack(&stack)
		, mContext(context)
	{
	}

	State::~State()
	{
	}

	void State::load(const std::string& filename)
	{
	}

	void State::requestStackPush(States::ID stateID)
	{
		mStack->pushState(stateID);
	}

	void State::requestStackPop()
	{
		mStack->popState();
	}

	void State::requestStackClear()
	{
		mStack->clearStates();
	}

	State::Context State::getContext() const
	{
		return mContext;
	}
}
