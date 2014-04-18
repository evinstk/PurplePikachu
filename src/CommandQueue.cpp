#include <TEMM/CommandQueue.hpp>

namespace temm
{

	void CommandQueue::push(const Command& command)
	{
		mQueue.push(command);
	}

	void CommandQueue::push(Command&& command)
	{
		mQueue.push(std::move(command));
	}

	Command CommandQueue::pop()
	{
		Command command = mQueue.front();
		mQueue.pop();
		return command;
	}

	bool CommandQueue::isEmpty() const
	{
		return mQueue.empty();
	}

}