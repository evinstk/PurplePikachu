#include <TEMM/GameState.hpp>

namespace temm
{

	GameState::GameState(StateStack& stack, Context context)
		: State(stack, context)
		, mOverworld(*context.window)
	{
	}

    void GameState::draw()
    {
		mOverworld.draw();
    }

    bool GameState::update(sf::Time dt)
    {
		mOverworld.update(dt);
        return false;
    }

    bool GameState::handleEvent(const sf::Event& event)
    {
        return false;
    }

}