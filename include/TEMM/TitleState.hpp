#ifndef TEMM_TITLE_STATE_HPP
#define TEMM_TITLE_STATE_HPP

#include <TEMM/State.hpp>

namespace temm
{
	class TitleState : public State
	{
	public:
		TitleState(StateStack& stack, Context context);

		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
	private:
	};
}

#endif
