#include <TEMM/GameState.hpp>

namespace temm
{

	GameState::GameState(StateStack& stack, Context context)
		: State(stack, context)
		, mOverworld(*context.window, Overworld::Tile::Grass, 64, 64)
	{
	}

    void GameState::draw()
    {
		mOverworld.draw();
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