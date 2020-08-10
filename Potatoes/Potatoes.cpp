#include "Potatoes.h"

Potatoes::Potatoes()
	: m_tokenizer(Tokenizer()),
	m_currentLineString(""),
	m_isInitialized(false),
	m_operatorIterator(0),
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

	if(m.empty())
	{
		return -1;
	}
	else
	{
		position = m.position();
		return position;
	}

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

	if(inputPos >= 1)
	{
	std::string rightSideString = inputString.substr(0,inputPos);
	std::string leftSideString = inputString.substr(inputPos+1, inputString.size()-1);

	outputStringList.push_back(rightSideString);

	}

	//Manage the priority operator calls. 

	if(m_operatorIterator >= 1)
	{
		m_operatorIterator = 1;
	}
	else
	{
		m_operatorIterator++;
	}

	int pos = positionMatch(m_operatorList[m_operatorIterator]);

	if(leftSideString.size() > 1)
	{
		splitString(outputStringList,inputString, pos);
	}
	else
	{
		outputStringList.push_back(leftSideString);
	}

}
