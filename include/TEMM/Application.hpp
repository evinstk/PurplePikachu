#ifndef TEMM_APPLICATION_HPP
#define TEMM_APPLICATION_HPP

#include <TEMM/StateStack.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

namespace temm
{
	class Application
	{
	public:
		Application(float fps);
		void run();
		void registerStates();
	private:
		void processInput();
		void update(sf::Time dt);
		void render();

		sf::RenderWindow mWindow;
		StateStack mStateStack;
		const sf::Time mTimePerFrame;
	};
}

#endif
