#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	queue.push(command);
}

Command CommandQueue::pop()
{
	Command c = queue.front();
	queue.pop();
	return c;
}

bool CommandQueue::isEmpty() const
{
	return queue.empty();
}
