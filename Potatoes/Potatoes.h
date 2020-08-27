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

	KeyWordArray getKeywordLUT();

private:

	Tokenizer m_tokenizer;	

	std::string m_currentLineString;

	KeyWordArray m_keywordLUT;

	//Priority Operator List. Used by the parser for splitting up the input line into strings for the tokenizer.

	bool m_isInitialized;
	int m_operatorIterator;
	std::vector<std::string> m_operatorList;
	std::vector<std::string> m_keywordList;

	void initializeOperatorList();

	bool parseForKeyword(std::vector<std::string>& outputStringList);

	int positionMatch(std::string& inputString, std::string inputOper);
	void splitString(std::vector<std::string>& outputStringList, std::string& inputString, int);

	std::string generateKeywordRegEx();


};

