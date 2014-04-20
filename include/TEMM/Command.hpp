#ifndef TEMM_COMMAND_HPP
#define TEMM_COMMAND_HPP

#include <TEMM/Category.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>

namespace temm
{
	class SceneNode;

	struct Command
	{
		typedef std::function<void(SceneNode&, sf::Time)> Action;
		Command();
		Action action;
		unsigned int category;
	};

	template <typename GameObject, typename Function>
	Command::Action derivedAction(Function fn)
	{
		return[=](SceneNode& node, sf::Time dt)
		{
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			fn(static_cast<GameObject&>(node), dt);
		};
	}
}

#endif