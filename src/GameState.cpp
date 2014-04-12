#include <TEMM/GameState.hpp>

namespace temm
{

	GameState::GameState(StateStack& stack, Context context)
		: State(stack, context)
	{
	}

    void GameState::draw()
    {
		Context context = getContext();
		context.window->clear(sf::Color(255, 0, 0, 255));
    }

    bool GameState::update(sf::Time dt)
    {
        return false;
    }

    bool GameState::handleEvent(const sf::Event& event)
    {
        return false;
    }

}