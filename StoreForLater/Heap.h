#pragma once
//Singleton


#include "CommonIncludes.h"

namespace Guts {
	class Heap
	{
	public:
		~Heap();

		static Heap getInstance();

	private:
		Heap(DataTypes::Size heapSize = DEFAULT_HEAP_SIZE);

	};
}
