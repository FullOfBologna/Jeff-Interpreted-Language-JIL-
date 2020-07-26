#include "FunctionTable.h"

Guts::FunctionTable::FunctionTable()
	: m_functionTable{nullptr}
{

}

Guts::FunctionTable::~FunctionTable()
{
	//Clean up the functions registered to the function table. 

	for (auto& function : m_functionTable)
	{
		delete function;
	}
}

Guts::FunctionTable* Guts::FunctionTable::getInstance()
{
	if (instance == nullptr)
	{
		instance = new FunctionTable();
	}

	return instance;
}

bool Guts::FunctionTable::registerFunction(Function* function)
{
	DataTypes::Id functionId = function->getFunctionId();

	if (functionId < MAX_FUNCTION_TABLE_SIZE)
	{
		if (m_functionTable[functionId] == nullptr)
		{
			m_functionTable[functionId] = function;
		}
		else
		{
			std::cout << "Error, function already exists." << std::endl;
			return false;
		}
	}
}
