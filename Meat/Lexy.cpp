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
	// m_inputTokenList = inputTokenList;
	// executeAnalyzedInstructions(inputTokenList);
	newExecutor(inputTokenList);
}

bool Lexy::isStored(std::string varName)
{
	auto iterator = m_storedVariables.find(varName);
	if (iterator == m_storedVariables.end())
		return false;
	return true;
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
	auto varPair = m_storedVariables.find(variableName);

	varPair->second = variableValue;
}

void Lexy::printStoredVariables()
{
	for (auto varPair : m_storedVariables)
	{
		std::cout << "Name: " << varPair.first << ", Value: " << varPair.second << std::endl;
	}
}

//Token List should be reversed, where the right most tokens are evaluated first. 

//Need to improve storing of variables. 


//First have some pre handling of tokens. 

//-> Find Operators on the right side first.
//
//	Store indexes of priority operators first. 
//
//	Makes sense to 
// 

bool Lexy::newExecutor(TokenList inputTokenList)
{
	std::deque<int> priorityIndexVector;

	findMathOperators(priorityIndexVector, inputTokenList);
	findEqualsOperator(priorityIndexVector, inputTokenList);

	TokenList newTokenList;

	std::cout << "Inside new Executor. Calculating Values: " << '\n';

	for(auto index : priorityIndexVector)
	{

		//Evaluate the expression at the index, and update the inputTokenList.
		Name name = getName(inputTokenList[index]);

		Token resultToken;

		bool isMult = (name == "MULT");
		bool isDiv = (name == "DIV");
		bool isAdd = (name == "ADD");
		bool isSub = (name == "SUB");

		bool isArithmetic = (isMult || isDiv || isAdd || isSub);

		std::cout << "Evaluating at index " << index << '\n';

		if(isArithmetic)
		{
			//Grab the left and right values. If numbers, evaluate the numbers. If names, recall Variable Value. 

			float leftVal, rightVal;

			Name leftName = getName(inputTokenList[index-1]);
			Name rightName = getName(inputTokenList[index+1]);

			if((leftName == "NUMBER") && (rightName == "NUMBER"))
			{
				float result;

				leftVal = atof(getValue(inputTokenList[index-1]).c_str());
				rightVal = atof(getValue(inputTokenList[index+1]).c_str());
				
				//TODO: Analyze for Unexpected Behavior

				if(isMult)
				{
					result = leftVal*rightVal;
				}

				if(isDiv)
				{
					float epsilon = 0.000000000000001;

					if(rightVal > epsilon)
					{
						result = leftVal/rightVal;						
					}
				}

				if(isAdd)
				{
					result = leftVal + rightVal;
				}

				if(isSub)
				{
					result = leftVal - rightVal;
				}

				resultToken = std::make_tuple("NUMBER", std::to_string(result));
			}
		}

		// std::vector<Token>::iterator leftIndex = find(inputTokenList.begin(),inputTokenList.end(), (index-1));
		// std::vector<Token>::iterator rightIndex = find(inputTokenList.begin(),inputTokenList.end(), (index+1));

		std::vector<Token>::iterator leftIter;
		std::vector<Token>::iterator rightIter;

		leftIter = std::begin(inputTokenList) + (index-1);
		leftIter = std::begin(inputTokenList) + (index-1);


		int leftIndex = (index - 1);
		int rightIndex = (index + 1);

		//GOAL: Delete the two numbers and the arithmetic operator, and replace all three with the resulting value. 
		// This could work even with variables eventually. 

		inputTokenList.erase(leftIter, rightIter);
		
		//Now that the original stuff is 

		inputTokenList.insert(leftIter, resultToken);
	}

	std::cout << "Printing Token List: " << '\n';
	for(auto& token : inputTokenList)
	{
		printToken(token);
	}

	return true;
}

bool Lexy::executeAnalyzedInstructions(TokenList inputTokenList) {
	//Run through the token list. 
		//Only Values for now. 
	std::vector<int> variableList;

	uint32_t iterator = 0;

	float valArray[2];

	for (auto& token : inputTokenList)
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

			// The EQUALS Operator needs to check if there are more expressions after the equals sign, to 
			// Fully evaluate the right side, before storing to the input name. 

			// TokenList rightSideTokenList = ;// Grab token list starting at Iterator +1.

			std::string variableName = getValue(inputTokenList[iterator - 1]);
			
			// Use the rest of the token list. 

			if (inputTokenList.size() - iterator > 1)
			{
				// More of the token list to parse. 

			}
			std::string variableValue = getValue(inputTokenList[iterator + 1]);

			//Check if the variableValue is NUMBER

			std::stringstream varStream(variableValue);

			float variableFloat;

			varStream >> variableFloat;

			updateMapValue(variableName, variableFloat);

			printStoredVariables();
			std::cout << std::endl;
		}
		else if (name == "NUMBER")
		{
			//Move on if Number. 
		}
		else if (name == "ADD")
		{
			//ADD can only add the previous number and the next number in the list. 

			//TODO : Refactor to be able to add either numbers or variables. 

			if (!getOperatorValues(valArray, iterator))
			{
				continue;
			};

			std::cout << "EVALUATING: " << valArray[0] << "+" << valArray[1] << " = " << valArray[0]+valArray[1] << std::endl;
		}
		else if (name == "SUB")
		{
			if (!getOperatorValues(valArray, iterator))
			{
				
				continue;
			}

			std::cout << "EVALUATING: " << valArray[0] << "-" << valArray[1] << " = " << valArray[0]-valArray[1] << std::endl;

		}
		else if (name == "MULT")
		{
			if (!getOperatorValues(valArray, iterator))
			{

				continue;
			}

			std::cout << "EVALUATING: " << valArray[0] << "*" << valArray[1] << " = " << valArray[0]*valArray[1] << std::endl;

		}
		else if (name == "DIV")
		{
			if (!getOperatorValues(valArray, iterator))
			{

				continue;
			}
			if (valArray[1] == 0.0)
			{
				std::cout << "Error: Not able to divide by 0." << std::endl;

				continue;
			}
			std::cout << "EVALUATING: " << valArray[0] << "/" << valArray[1] << " = " << valArray[0]/valArray[1] << std::endl;

		}
		else
		{
			std::cout << "Error " << getValue(token) << std::endl;
			break;
		}

		iterator++;
	}

	//If no more to parse, return false.
	return false;
}

bool Lexy::getOperatorValues(float* outputFloatArray, uint32_t iterator)
{
	Name lhsName = getName(m_inputTokenList[iterator - 1]);
	Name rhsName = getName(m_inputTokenList[iterator + 1]);

	if ((lhsName == "ERROR") || (rhsName == "ERROR"))
	{
		std::cout << "Error. Unable to evaluate sum. " << std::endl;
		return false;
	}

	std::string lhsVal = getValue(m_inputTokenList[iterator - 1]);
	std::string rhsVal = getValue(m_inputTokenList[iterator + 1]);

	std::stringstream lhsStream(lhsVal);
	std::stringstream rhsStream(rhsVal);

	lhsStream >> outputFloatArray[0];
	rhsStream >> outputFloatArray[1];

	return true;

}

bool Lexy::findMathOperators(std::deque<int>& indexDeque, TokenList& inputTokenList)
{
	bool foundOperators = false;

	int listLength = inputTokenList.size();

	//Left Associative Operators for both, so push_back. 
	foundOperators = findMultDivOps(indexDeque, inputTokenList);
	foundOperators = findAddSubOps(indexDeque, inputTokenList);

	return foundOperators;
}

bool Lexy::findMultDivOps(std::deque<int>& indexDeque, TokenList& inputTokenList)
{
	bool foundOperators = false;

	int listLength = inputTokenList.size();

	for(int index = 0; index < listLength; index++)
	{
		Name name = getName(inputTokenList[index]);

		if((name == "MULT") || (name == "DIV"))
		{
			indexDeque.push_back(index);
			foundOperators = true;
		}
	}

	return foundOperators;
}

bool Lexy::findAddSubOps(std::deque<int>& indexDeque, TokenList& inputTokenList)
{
	bool foundOperators = false;

	int listLength = inputTokenList.size();

	for(int index = 0; index < listLength; index++)
	{
		Name name = getName(inputTokenList[index]);

		if((name == "ADD") || (name == "SUB"))
		{
			indexDeque.push_back(index);
			foundOperators = true;
		}
	}

	return foundOperators;
}


bool Lexy::findEqualsOperator(std::deque<int>& indexDeque, TokenList& inputTokenList)
{
	bool foundOperators = false;

	int listLength = inputTokenList.size();

	for(int index = 0; index < listLength; index++)
	{
		Name name = getName(inputTokenList[index]);

		if(name == "EQUALS")
		{
			indexDeque.push_back(index);
			foundOperators = true;
		}
	}

	return foundOperators;
}