#include "Lexy.h"

Lexy::Lexy() : 
	m_storedVariables{},
	m_inputTokenList{}
{

}

Lexy::~Lexy()
{

}

void Lexy::setOverallTokenList(TokenList inputTokenList)
{
	m_inputTokenList = inputTokenList;
	executeAnalyzedInstructions();
}

bool Lexy::isStored(std::string varName)
{
	for (auto& varPair : m_storedVariables)
	{
		if (varName == varPair.first)
		{
			return true;
		}
	}

	return false;
}

void Lexy::storeVariable(std::string varName)
{
	//Already checked that variable is not stored. 

	std::pair<std::string, float> newVariable;
	newVariable.first = varName;
	newVariable.second = 0;
	m_storedVariables.insert(newVariable);
}

void Lexy::updateMapValue(std::string variableName, float variableValue)
{

}

void Lexy::executeAnalyzedInstructions() {
	//Run through the token list. 
		//Only Values for now. 
	std::vector<int> variableList;

	uint32_t iterator = 0;

	for (auto& token : m_inputTokenList)
	{
		Name name = getName(token);
		if (name == "NAME")
		{
			std::string value = getValue(token);
			if (!isStored(value))
			{
				storeVariable(value);
			}
		}
		else if (name == "EQUALS")
		{
			// an equals operator indicates setting a value to a variable. 
			// as such, this should look at the previous token for the "name"
			// and the next iterator for the value to store. This will then set the value of
			// the map pair with the associated name. 

			std::string variableName = getValue(m_inputTokenList[iterator - 1]);
			std::string variableValue = getValue(m_inputTokenList[iterator + 1]);

			//Check if the variableValue is NUMBER

			std::stringstream varStream(variableValue);

			float variableFloat;

			varStream >> variableFloat;

			updateMapValue(variableName, variableFloat);

		}
		else if (name == "NUMBER")
		{
		}
		else if (name == "ADD")
		{
			//ADD can only add the previous number and the next number in the list. 

			//TODO : Refactor to be able to add either numbers or variables. 

			// Check both input for ERRORs

			Name lhsName = getName(m_inputTokenList[iterator - 1]);
			Name rhsName = getName(m_inputTokenList[iterator + 1]);

			if ((lhsName == "ERROR") || (rhsName == "ERROR"))
			{
				std::cout << "Error. Unable to evaluate sum. " << std::endl;
				continue;
			}

			std::string lhsVal = getValue(m_inputTokenList[iterator - 1]);
			std::string rhsVal = getValue(m_inputTokenList[iterator + 1]);

			std::stringstream lhsStream(lhsVal);
			std::stringstream rhsStream(rhsVal);

			int lhs;
			int rhs;

			lhsStream >> lhs;
			rhsStream >> rhs;

			std::cout << "EVALUATING: " << lhs << " + " << rhs << " = " << lhs + rhs << std::endl;
		}
		else
		{
			std::cout << "Error " << getValue(token) << std::endl;
			break;
		}

		iterator++;
	}

	m_inputTokenList.clear();
}

