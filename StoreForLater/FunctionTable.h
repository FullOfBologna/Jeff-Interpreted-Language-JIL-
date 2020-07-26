#pragma once

#include "CommonIncludes.h"

#include <array>
#include "Function.h"

//	Singleton
// "THERE CAN ONLY BE ONE FUNCTION TABLE"
//
//
//

class FunctionTable
{
public:
	~FunctionTable();

	FunctionTable* getInstance();

	bool registerFunction(Function*);

private:
	FunctionTable();

	static FunctionTable* instance;

	std::array<Function*, 256> m_functionTable;

};
