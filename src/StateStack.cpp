#include <TEMM/StateStack.hpp>
#include <cassert>

namespace temm
{
	StateStack::StateStack(State::Context context)
		: mContext(context)
	{
	}

	State::Ptr StateStack::createState(States::ID stateID)
	{
		auto found = mFactories.find(stateID);
		assert(found != mFactories.end());

		return found->second();
	}

	void StateStack::applyPendingChanges()
	{
		for (PendingChange change : mPendingList)
		{
			switch (change.action)
			{
			case Push:
				mStack.push_back(createState(change.stateID));
				break;
			case Pop:
				mStack.pop_back();
				break;
			case Clear:
				mStack.clear();
				break;
			}
		}
		mPendingList.clear();
	}

	void StateStack::handleEvent(const sf::Event& event)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		{
			if (!(*itr)->handleEvent(event))
				break;
		}
		applyPendingChanges();
	}

	void StateStack::update(sf::Time dt)
	{
		for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		{
			if (!(*itr)->update(dt))
				break;
		}
		applyPendingChanges();
	}

	void StateStack::draw()
	{
		for (auto& ptr : mStack)
		{
			ptr->draw();
		}
	}

	void StateStack::pushState(States::ID stateID)
	{
		mPendingList.push_back(PendingChange(Push, stateID));
	}

	void StateStack::popState()
	{
		mPendingList.push_back(PendingChange(Pop));
	}

	void StateStack::clearStates()
	{
		mPendingList.push_back(PendingChange(Clear));
	}

	bool StateStack::isEmpty() const
	{
		return mStack.empty();
	}

	StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
		: action(action)
		, stateID(stateID)
	{
	}
}