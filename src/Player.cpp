#include <TEMM/Player.hpp>
#include <TEMM/CommandQueue.hpp>
#include <TEMM/Mob.hpp>
#include <SFML/Window/Event.hpp>

namespace temm
{

	using namespace std::placeholders;

	struct MobMover
	{
		MobMover(float vx, float vy, int identifier)
		: velocity(vx, vy)
		, mobID(identifier)
		{
		}

		void operator() (Mob& mob, sf::Time) const
		{
			if (mob.getIdentifier() == mobID)
				mob.setVelocity(velocity);
		}

		sf::Vector2f velocity;
		int mobID;
	};

	Player::Player(sf::Int32 identifier, const KeyBinding* binding)
		: mKeyBinding(binding)
		, mIdentifier(identifier)
	{
		initializeActions();

		for (auto& pair : mActionBinding)
			pair.second.category = Category::Player;
	}

	void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			Action action;
			if (mKeyBinding && mKeyBinding->checkAction(event.key.code, action) && !isRealtimeAction(action))
			{
				commands.push(mActionBinding[action]);
			}
		}
	}

	void Player::handleRealtimeInput(CommandQueue& commands)
	{
		std::vector<Action> activeActions = mKeyBinding->getRealtimeActions();
		for (Action action : activeActions)
			commands.push(mActionBinding[action]);
	}

	void Player::initializeActions()
	{
		mActionBinding[PlayerAction::MoveLeft].action = derivedAction<Mob>(MobMover(-15, 0, mIdentifier));
		mActionBinding[PlayerAction::MoveRight].action = derivedAction<Mob>(MobMover(15, 0, mIdentifier));
		mActionBinding[PlayerAction::MoveUp].action = derivedAction<Mob>(MobMover(0, -15, mIdentifier));
		mActionBinding[PlayerAction::MoveDown].action = derivedAction<Mob>(MobMover(0, 15, mIdentifier));
	}

}
