#pragma once

#include <map>
#include <regex>
#include <iterator>

#include "Tokenizer.h"
#include "../Utils/CommonIncludes.h"
class Potatoes
{
public:
	Potatoes();
	~Potatoes();

	void setLine(std::string&);

	TokenList parseLine();

private:

	Tokenizer m_tokenizer;	

	std::string m_currentLineString;

	//Priority Operator List. Used by the parser for splitting up the input line into strings for the tokenizer.

	bool m_isInitialized;
	int m_operatorIterator;
	std::vector<std::string> m_operatorList;

	void initializeOperatorList();

	int positionMatch(std::string& inputString, std::string inputOper);
	void splitString(std::vector<std::string>& outputStringList, std::string& inputString, int);
};

