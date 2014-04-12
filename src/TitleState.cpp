#include <TEMM/TitleState.hpp>

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
		// Update TitleState stuff
		return true;
	}

	bool TitleState::handleEvent(const sf::Event& event)
	{
		// Handle events for TitleState
		return true;
	}
}