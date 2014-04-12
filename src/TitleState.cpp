#include <TEMM/TitleState.hpp>
#include <SFML/Window/Event.hpp>

namespace temm
{
	TitleState::TitleState(StateStack& stack, Context context)
		: State(stack, context)
	{
		// TitleState stuff
	}

	void TitleState::draw()
	{
		// Draw TitleState stuff
	}

	bool TitleState::update(sf::Time dt)
	{
		return true;
	}
	
	bool TitleState::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			requestStackClear();
			requestStackPush(States::ID::Game);
		}
		return true;
	}
}