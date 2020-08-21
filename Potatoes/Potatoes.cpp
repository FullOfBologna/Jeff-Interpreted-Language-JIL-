#include "Potatoes.h"

Potatoes::Potatoes()
	: m_tokenizer(Tokenizer()),
	m_currentLineString(""),
	m_keywordLUT(m_tokenizer.getKeywordArray()),
	m_isInitialized(false),
	m_operatorIterator(0),
	m_operatorList{}	
{

	initializeOperatorList();
	print("Done building regex.");
}

Potatoes::~Potatoes()
{

}

void Potatoes::setLine(std::string& line)
{
	m_currentLineString = line;
}

TokenList Potatoes::parseLine()
{
	std::vector<std::string> parsedStringList;
	TokenList tokenList;

	std::string tempString = "";

	int pos = -1;

	print("Before regex matching.");

	//Search line for keyWords first. 

	parseForKeyword(outputStringList);

	pos = -1;

	// //Match Arithmetic Operators
	// pos = positionMatch(m_currentLineString, m_operatorList[1]);

	// std::vector<std::string> outputStringList;

	// if(m_currentLineString.size() < 1)
	// {
	// 	return tokenList;
	// }

	// splitString(outputStringList, m_currentLineString, pos);	


	std::cout << "Output String List = {";
	for(auto outputString : outputStringList)
	{
		std::cout << outputString << ",";
	}
	std::cout << "}" << std::endl;

	for (auto& str : outputStringList)
	{
		Token token;

		token = m_tokenizer.generateToken(str);

		// std::cout << "Token = {" << getName(token) << ", " << getValue(token) << "}" << std::endl;

		tokenList.push_back(token);
	}

	return tokenList;
}

void Potatoes::parseForKeyword()
{
	int pos = positionMatch(m_currentLineString,m_operatorList[0]);


}

// void Potatoes::splitArithmeticOperators()

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
		std::cout << "Full Match: " << m[0] << '\n';
		return position;
	}

}

void Potatoes::initializeOperatorList()
{
	if(!m_isInitialized)
	{
		
		std::string regExKeyWordString = generateKeywordRegEx();

		print(regExKeyWordString.c_str());

		m_operatorList.push_back(regExKeyWordString);

		// = sign is the highest priority after keywords.
		m_operatorList.push_back("\=");

		//Place Brackets here once ready to implement

		//Add arithmetic Operators
		m_operatorList.push_back("[\+\-\/\*\%\^]");

		//EmptyBrackets with nothing in the middle indicates a new list. 

		//m_operatorList.push_back("\{\}");

		m_isInitialized = true;
	}
}

//Example Keyword regex generated from this method is:
//
//	(?:[\s]|^)((print)|(do)|(while))\((.*)\)(?=[\s]|$)
//
//	Refer to this example for what the regex is matching. https://regex101.com/r/uRWvgx/5
//
//	Current limitation is even keywords like break will require parenthesis
// 		which is like syntactic salt not sugar :(
//
//	Uses the keyword Look up table to generate the regex to match. 

std::string Potatoes::generateKeywordRegEx()
{
	std::string regEx("(?:[\s]|^)(");

	for(int index = 0; index < NUM_KEYWORDS; index++)
	{
		regEx.append("\(");
		regEx.append(m_keywordLUT[index]);
		regEx.append("\)");

		if(index < NUM_KEYWORDS-1)
		{
			regEx.append("|");
		}
	}
	regEx.append(")\((.*)\)(?=[\s]|$)");

	return regEx;
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

	if(m_operatorIterator >= 2)
	{
		m_operatorIterator = 2;
	}
	else
	{
		m_operatorIterator++;
	}

	std::cout << m_operatorIterator << '\n';

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
