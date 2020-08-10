#pragma once

#include <string>
#include <cctype>

#include "../Utils/CommonIncludes.h"


class Tokenizer
{
public:
	Tokenizer();
	~Tokenizer();

	Token generateToken(std::string input);

private:
	const TokenNameArray m_tokenLUT;

	TokenNameArray initializeTokenArray();
	Name interpretToken(std::string input);
	void stripSpaces(std::string& input);
};

