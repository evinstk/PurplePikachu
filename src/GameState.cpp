#include <TEMM/GameState.hpp>
#include <SFML/Window/Event.hpp>

namespace temm
{

	GameState::GameState(StateStack& stack, Context context)
		: State(stack, context)
		, mOverworld(*context.window)
		, mPlayer(1, context.keys1)
	{
	}

    void GameState::draw()
    {
		mOverworld.draw();
    }

    bool GameState::update(sf::Time dt)
    {
		mOverworld.update(dt);

		CommandQueue& commands = mOverworld.getCommandQueue();
		mPlayer.handleRealtimeInput(commands);

        return false;
    }

    bool GameState::handleEvent(const sf::Event& event)
    {
		CommandQueue& commands = mOverworld.getCommandQueue();
		mPlayer.handleEvent(event, commands);

        return false;
    }

}