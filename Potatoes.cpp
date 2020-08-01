#include "Potatoes.h"

Potatoes::Potatoes()
	: m_tokenizer(Tokenizer()),
	m_currentLine("")
{

}

Potatoes::~Potatoes()
{

}

void Potatoes::setLine(std::string& line)
{
	m_currentLine = line;
}

TokenList Potatoes::parseLine()
{
	std::vector<std::string> parsedStringList;
	TokenList tokenList;

	bool isFirstChar = true;
	std::string tempString = "";

	for (uint32_t i = 0; i < m_currentLine.size(); i++)
	{
		//Nothing to parse. Move on.

		char val = m_currentLine[i];

		if (isFirstChar && (std::isspace(val)))
		{
			tempString = "";
			continue;
		}
		
		if (isFirstChar && ((val == '+') || (val == '-') || (val == '*') || (val == '/')))
		{
			tempString += val;
			parsedStringList.push_back(tempString);
			continue;
		}

		if (!isFirstChar && (!std::isspace(val)))
		{
			tempString += val;
		}

		if (isFirstChar && (isNumber(tempString)))
		{
			tempString += val;
			isFirstChar = false;
		}
		else if(!isFirstChar && ((std::isspace(val)) || (i == (m_currentLine.size()-1))))
		{
			parsedStringList.push_back(tempString);
			tempString = "";
			isFirstChar = true;
		}
	}

	for (auto& str : parsedStringList)
	{
		Token token;

		token = m_tokenizer.generateToken(str);
		tokenList.push_back(token);
	}

	return tokenList;
}
