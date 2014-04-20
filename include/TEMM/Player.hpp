#ifndef TEMM_PLAYER_HPP
#define TEMM_PLAYER_HPP

#include <TEMM/KeyBinding.hpp>
#include <TEMM/Command.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace sf
{
	class Event;
}

namespace temm
{

	class CommandQueue;

	class Player : private sf::NonCopyable
	{
	public:
		typedef PlayerAction Action;

		Player(sf::Int32 identifier, const KeyBinding* binding);

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleRealtimeInput(CommandQueue& commands);
				
	private:
		void initializeActions();

		const KeyBinding* mKeyBinding;
		std::map<Action, Command> mActionBinding;
		int mIdentifier;
	};

}

#endif
