#pragma once

// "Stack" simulates a very rudimentary traditional LIFO Buffer of method calls.
// This handles what functions should be called, when. 
//
//	For reference - https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
//

#include "DataTypes.h"
#include "Function.h"
#include "Heap.h"

#include <list>

namespace Guts {


/// <summary>
///	This is not a singleton, because it is possible to have multiple stacks at the same time.
///	This would have to be a future consideration (Essentially a rudimentary multithreading.)
///
///
/// </summary>

class Stack
{
public:
	Stack(DataTypes::Size maxSize, Guts::Heap heap);
	~Stack();

	Guts::Function* getCurrentFunction();

	void addToQueue(Guts::Function*);

private:

	//Should be the first function on the queue, as the stack needs 
	// to be handled sequentially. 
	void removeFromQueue();

	// queue is the waiting functions to be called. 
	std::list<Guts::Function*> m_queue;

	Heap m_heap;
};

}