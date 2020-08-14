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

	pos = positionMatch(m_currentLineString, m_operatorList[0]);

	std::vector<std::string> outputStringList;

	if(m_currentLineString.size() < 1)
	{
		return tokenList;
	}

	splitString(outputStringList, m_currentLineString, pos);	

	// std::cout << "Output String List = {";
	// for(auto outputString : outputStringList)
	// {
	// 	std::cout << outputString << ",";
	// }
	// std::cout << "}" << std::endl;

	for (auto& str : outputStringList)
	{
		Token token;

		token = m_tokenizer.generateToken(str);

		// std::cout << "Token = {" << getName(token) << ", " << getValue(token) << "}" << std::endl;

		tokenList.push_back(token);
	}

	return tokenList;
}



int Potatoes::positionMatch(std::string& inputString,std::string inputOper)
{
	std::string regExString = inputOper;

	// std::cout << "RegExString: " << regExString << std::endl;
	std::regex r(regExString);

	std::smatch m;

	int position;

	std::regex_search(inputString, m, r);

	if(m.empty())
	{
		return -1;
	}
	else
	{
		position = m.position(0);

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

	// std::cout << "inputString: " << inputString << std::endl;

	std::string leftSideString = inputString.substr(0,inputPos);
	std::string rightSideString = inputString.substr(inputPos+1, inputString.size()-1);

	// std::cout << leftSideString << "      " << rightSideString << std::endl; 

	outputStringList.push_back(leftSideString);
	outputStringList.push_back(inputString.substr(inputPos,1));

	//Manage the priority operator calls. 

	if(m_operatorIterator >= 1)
	{
		m_operatorIterator = 1;
	}
	else
	{
		m_operatorIterator++;
	}

	std::string opString;

	int pos = positionMatch(rightSideString,m_operatorList[m_operatorIterator]);
	// std::cout << "pos = " << pos << std::endl;

	if(pos != -1)
	{
		splitString(outputStringList,rightSideString, pos);
	}
	else
	{
		outputStringList.push_back(rightSideString);
		return;
	}
}
