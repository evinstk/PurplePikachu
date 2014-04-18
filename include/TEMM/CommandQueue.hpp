#ifndef TEMM_COMMAND_QUEUE_HPP
#define TEMM_COMMAND_QUEUE_HPP

#include <TEMM/Command.hpp>
#include <queue>

namespace temm
{

	class CommandQueue
	{
	public:
		void push(const Command& command);
		void push(Command&& command);
		Command pop();
		bool isEmpty() const;

	private:
		std::queue<Command> mQueue;
	};

}

#endif
