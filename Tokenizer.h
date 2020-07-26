#pragma once

#include <string>
#include <cctype>

#include "commonIncludes.h"


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

};

