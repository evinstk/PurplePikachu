#ifndef TEMM_STATE_STACK_HPP
#define TEMM_STATE_STACK_HPP

#include <TEMM/State.hpp>
#include <vector>
#include <map>
#include <functional>

namespace temm
{
	class StateStack
	{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		explicit StateStack(State::Context context);

		template<typename T>
		void registerState(States::ID stateID);

		void update(sf::Time dt);
		void draw();
		void handleEvent(const sf::Event& event);

		void pushState(States::ID stateID);
		void popState();
		void clearStates();

		bool isEmpty() const;
	private:
		State::Ptr createState(States::ID stateID);
		void applyPendingChanges();

		struct PendingChange
		{
			explicit PendingChange(Action action, States::ID stateID = States::None);
			Action action;
			States::ID stateID;
		};

		std::vector<State::Ptr> mStack;
		std::vector<PendingChange> mPendingList;
		State::Context mContext;
		std::map<States::ID, std::function<State::Ptr()>> mFactories;
	};
}

#include "StateStack.inl"

#endif
