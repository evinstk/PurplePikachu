#ifndef TEMM_KEY_BINDING_HPP
#define TEMM_KEY_BINDING_HPP

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <map>

namespace temm
{

	enum class PlayerAction
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Count,
	};

	class KeyBinding
	{
	public:
		typedef PlayerAction Action;

		explicit KeyBinding(int controlPreconfiguration);

		void assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key getAssignedKey(Action action) const;

		bool checkAction(sf::Keyboard::Key key, Action& out) const;
		std::vector<Action> getRealtimeActions() const;

	private:
		void initializeActions();

		std::map<sf::Keyboard::Key, Action> mKeyMap;
	};

	bool isRealtimeAction(PlayerAction action);

}

#endif
