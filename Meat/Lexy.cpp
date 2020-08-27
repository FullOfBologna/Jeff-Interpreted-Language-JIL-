#include "Lexy.h"

Lexy::Lexy(KeyWordArray keywordLUT) : 
	m_storedVariables{},
	m_inputTokenList{},
	m_keywordHandler(keywordLUT)
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

void Lexy::getMapValue(float& outputFloat, std::string variableName)
{
	outputFloat = m_storedVariables.find(variableName)->second;
}

void Lexy::printStoredVariables()
{
	std::cout << "STORED VARIABLES: " << '\n';

	for (auto varPair : m_storedVariables)
	{
		std::cout << "Name: " << varPair.first << ", Value: " << varPair.second << '\n';
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

	//Separate Keyword and argument logic from the arithmetic.

	if(performKeywordAnalysis(inputTokenList))
	{

	} 
	else if(!performArithmetic(inputTokenList))
	{
		std::cout << "ERROR: Error performing arithmetic." << '\n';
		return false;
	}

	performLogic(inputTokenList);

	// printStoredVariables();		

	return true;

}

//Work on the keywords
bool Lexy::performKeywordAnalysis(TokenList& inputTokenList)
{
	//Create a keyword handler object, which has the functions definitions. 

	auto tokenListSize = inputTokenList.size();

	m_keywordHandler.setStoredVariables(m_storedVariables);

	bool keywordFound = false;
	for(int tokenIt = 0; tokenIt < tokenListSize; tokenIt++)
	{
		std::string keywordValue = "";
		std::string argValue = "";
		if(getName(inputTokenList[tokenIt]) == "KEYWD")
		{
			keywordValue = getValue(inputTokenList[tokenIt]);
			m_keywordHandler.setKeyword(keywordValue);
			keywordFound = true;
		}

		if(getName(inputTokenList[tokenIt]) == "ARG")
		{
			argValue = getValue(inputTokenList[tokenIt]);
			m_keywordHandler.setArg(argValue);
		}
	}

	m_keywordHandler.executeKeyword();

	return keywordFound;
}

bool Lexy::performLogic(TokenList& inputTokenList)
{
	// print("Analyzing Input Token List");

	// printTokenList(inputTokenList);

	int listSize = inputTokenList.size();
	for(int index = 0; index < listSize; index++)
	{
		Name name = getName(inputTokenList[index]);

		if(name == "EQUALS")
		{
			int leftIndex = index-1;
			int rightIndex = index+1;

			if(index < 1)
			{
				print("ERROR: No Left hand Value.");
				return false;
			}

			Name varTokenName = getName(inputTokenList[leftIndex]);
			std::string var = getValue(inputTokenList[leftIndex]);

			if(varTokenName != "NAME")
			{
				print("ERROR: Invalid variableName on left hand side. ");
				return false;
			}

			if(rightIndex > (listSize-1))
			{
				print("ERROR: Nothing to assign on right hand side. ");
				return false;
			}

			std::string rightName = getName(inputTokenList[rightIndex]);
			std::string rightValue = getValue(inputTokenList[rightIndex]);
			float rightValueFloat;

			if(rightName == "NUMBER")
			{
				//Convert right Value to float
				rightValueFloat = stof(rightValue);
			}
			else if(rightName == "NAME")
			{
				// print("Storing variable into another variable.");

				if(isStored(rightValue))
				{
					getMapValue(rightValueFloat, rightValue);
				}
			}

			if(!isStored(var))
			{
				storeVariable(var);
			}

			updateMapValue(var,rightValueFloat);

		}
	}

	return true;
}

bool Lexy::performArithmetic(TokenList& IOTokenList)
{
	std::deque<int> priorityIndexVector;

	findMathOperators(priorityIndexVector, IOTokenList);
	findEqualsOperator(priorityIndexVector, IOTokenList);

	TokenList newTokenList;

	int prevIndex = 0;

	// std::cout << "Inside new Executor. Calculating Values: " << '\n';

	// std::cout << "Priority IndexList = ";

	// for(auto index : priorityIndexVector)
	// {
	// 	std::cout << index << ',';
	// }

	// std::cout << '\n';


	// BIG ISSUE: TODO: Need to store a temp vector 

	int priorityIndexLen = priorityIndexVector.size();

	for(int curIndex = 0; curIndex < priorityIndexLen; curIndex++)
	{
		int diff = 0;

		int index = priorityIndexVector[curIndex];

		int endIndex = priorityIndexLen-1;

		if(index > prevIndex && (prevIndex != 0))
		{
			diff = index-prevIndex;
		}

		int newIndex = index-diff;

		// std::cout << "Evaluating at index " << newIndex << '\n';

		// std::cout << "Index = " << index << '\n';

		//Evaluate the expression at the index, and update the IOTokenList.
		Name name = getName(IOTokenList[newIndex]);

		Token resultToken;

		bool isMult = (name == "MULT");
		bool isDiv = (name == "DIV");
		bool isAdd = (name == "ADD");
		bool isSub = (name == "SUB");

		bool isArithmetic = (isMult || isDiv || isAdd || isSub);

		// std::cout << "Evaluating at index " << newIndex << '\n';

		if(isArithmetic)
		{
			//Grab the left and right values. If numbers, evaluate the numbers. If names, recall Variable Value. 

			float leftVal, rightVal, result;

			Name leftName = getName(IOTokenList[newIndex-1]);
			Name rightName = getName(IOTokenList[newIndex+1]);

			leftVal = atof(getValue(IOTokenList[newIndex-1]).c_str());
			rightVal = atof(getValue(IOTokenList[newIndex+1]).c_str());

			//Overwrite leftVal or rightVal of token NAME

			if(leftName == "NAME")
			{
				std::string leftVarName = getValue(IOTokenList[newIndex-1]);
				//Grab the stored variable and set leftVal = to it. 
				if(!isStored(leftVarName))
				{
					std::cout << "ERROR: Unknown variable: " << leftVarName << ". Quitting." << '\n';
					return false;
				}

				getMapValue(leftVal, leftVarName);

				// std::cout << "LEFT VALUE = " << leftVal << '\n';
			}

			if(rightName == "NAME")
			{
				std::string rightVarName = getValue(IOTokenList[newIndex+1]);
				//Grab the stored variable and set leftVal = to it. 
				if(!isStored(rightVarName))
				{
					std::cout << "ERROR: Unknown variable: " << rightVarName << ". Quitting." << '\n';
					return false;
				}

				getMapValue(rightVal, rightVarName);

				// std::cout << "RIGHT VALUE = " << rightVal << '\n';

			}

			
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

		// std::vector<Token>::iterator leftIndex = find(IOTokenList.begin(),IOTokenList.end(), (index-1));
		// std::vector<Token>::iterator rightIndex = find(IOTokenList.begin(),IOTokenList.end(), (index+1));

		// std::cout << "Before iterators defined. " << '\n';

		std::vector<Token>::iterator leftIter;
		std::vector<Token>::iterator rightIter;

		leftIter = std::begin(IOTokenList) + (newIndex-1);
		rightIter = std::begin(IOTokenList) + (newIndex+1);


		int leftIndex = (newIndex - 1);
		int rightIndex = (newIndex + 1);

		//GOAL: Delete the two numbers and the arithmetic operator, and replace all three with the resulting value. 
		// This could work even with variables eventually. 

		// std::cout << "tokenList prior to erase: " << '\n';

		// printTokenList(IOTokenList);

		// 

		if(curIndex < endIndex)
		{
			leftIter = IOTokenList.erase(leftIter, rightIter+1);

			// std::cout << "Result Token = ";

			// printToken(resultToken);

			IOTokenList.insert(leftIter, resultToken);

			// std::cout << "Printing Token List: " << '\n';
			// for(auto& token : IOTokenList)
			// {
			// 	printToken(token);
			// }

			prevIndex = newIndex;
		}
	}

	// std::cout << "RESULTANT Token List: " << '\n';

	// printTokenList(IOTokenList);

	//done with arithmetic

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

			// printStoredVariables();
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

			// std::cout << "EVALUATING: " << valArray[0] << "+" << valArray[1] << " = " << valArray[0]+valArray[1] << std::endl;
		}
		else if (name == "SUB")
		{
			if (!getOperatorValues(valArray, iterator))
			{
				
				continue;
			}

			// std::cout << "EVALUATING: " << valArray[0] << "-" << valArray[1] << " = " << valArray[0]-valArray[1] << std::endl;

		}
		else if (name == "MULT")
		{
			if (!getOperatorValues(valArray, iterator))
			{

				continue;
			}

			// std::cout << "EVALUATING: " << valArray[0] << "*" << valArray[1] << " = " << valArray[0]*valArray[1] << std::endl;

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
			// std::cout << "EVALUATING: " << valArray[0] << "/" << valArray[1] << " = " << valArray[0]/valArray[1] << std::endl;

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