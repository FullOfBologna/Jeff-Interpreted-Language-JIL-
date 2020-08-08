#include "Potatoes.h"

Potatoes::Potatoes()
	: m_tokenizer(Tokenizer()),
	m_currentLineString(""),
	m_isInitialized(false),
	m_operatorList{}	
{
	initializeOperatorList();
}

Potatoes::~Potatoes()
{

}

void Potatoes::setLine(std::string& line)
{
	m_currentLineString = line;
}

//TODO: Creating a more sophisticated parser. 

TokenList Potatoes::parseLine()
{
	std::vector<std::string> parsedStringList;
	TokenList tokenList;

	std::string tempString = "";

	int pos = -1;

	pos = positionMatch(m_operatorList[0]);

	std::vector<std::string> outputStringList;

	if(m_currentLineString.size() < 1)
	{
		return tokenList;
	}

	splitString(outputStringList, m_currentLineString, pos);	
	std::cout << "Right Side String:" << outputStringList[0] << ", Left Side String" << outputStringList[1] << std::endl;


	pos = positionMatch(m_operatorList[1]);

	std::vector<std::string> secondOutputStringList;

	if(m_currentLineString.size() < 1)
	{
		return tokenList;
	}

	if((pos-outputStringList[0].size() < 1))
	{
		return tokenList;
	}
	splitString(secondOutputStringList, outputStringList[1], pos-(outputStringList[0].size()));	
	std::cout << "Right Side String:" << secondOutputStringList[0] << ", Left Side String" << secondOutputStringList[1] << std::endl;

	if(pos == -1)
	{
		//NO = sign found. 
	}

	// for (uint32_t i = 0; i < m_currentLine.size(); i++)
	// {
	// 	//Nothing to parse. Move on.

	// 	char val = m_currentLine[i];



	// 	// if (isFirstChar && (std::isspace(val)))
	// 	// {
	// 	// 	tempString = "";
	// 	// 	continue;
	// 	// }
		
	// 	// if (isFirstChar && ((val == '+') || (val == '-') || (val == '*') || (val == '/')))
	// 	// {
	// 	// 	tempString += val;
	// 	// 	parsedStringList.push_back(tempString);
	// 	// 	continue;
	// 	// }

	// 	// if (!isFirstChar && (!std::isspace(val)))
	// 	// {
	// 	// 	tempString += val;
	// 	// }

	// 	// if (isFirstChar && (isNumber(tempString)))
	// 	// {
	// 	// 	tempString += val;
	// 	// 	isFirstChar = false;
	// 	// }
	// 	// else if(!isFirstChar && ((std::isspace(val)) || (i == (m_currentLine.size()-1))))
	// 	// {
	// 	// 	parsedStringList.push_back(tempString);
	// 	// 	tempString = "";
	// 	// 	isFirstChar = true;
	// 	// }
	// }

	for (auto& str : parsedStringList)
	{
		Token token;

		token = m_tokenizer.generateToken(str);
		tokenList.push_back(token);
	}

	return tokenList;
}

int Potatoes::positionMatch(std::string inputOper)
{
	std::string regExString = inputOper;

	std::cout << "RegExString: " << regExString << std::endl;
	std::regex r(regExString);

	std::smatch m;

	int position;

	std::regex_search(m_currentLineString, m, r);

	position = m.position();

	return position;

}

void Potatoes::initializeOperatorList()
{
	if(!m_isInitialized)
	{
		// = sign is the highest priority.
		m_operatorList.push_back("\=");

		//Place Brackets here once ready to implement

		//Add arithmetic Operators
		m_operatorList.push_back("[\+\-\/\*\%\^]");

		m_isInitialized = true;
	}
}

void Potatoes::splitString(std::vector<std::string>& outputStringList, std::string& inputString, int inputPos)
{
	std::string rightSideString = inputString.substr(0,inputPos);
	std::string leftSideString = inputString.substr(inputPos+1, inputString.size()-1);

	outputStringList.push_back(rightSideString);
	outputStringList.push_back(leftSideString);	
}
