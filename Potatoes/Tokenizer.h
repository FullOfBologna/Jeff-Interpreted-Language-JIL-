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

	KeyWordArray getKeywordArray();

private:
	const TokenNameArray m_tokenLUT;
	const KeyWordArray m_keywordLUT;

	TokenNameArray initializeTokenArray();
	KeyWordArray initializeKeywordArray();

	Name interpretToken(std::string input);
	void stripSpaces(std::string& input);
};

