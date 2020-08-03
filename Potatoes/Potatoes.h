#pragma once

#include <map>

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

	std::string m_currentLine;

};

