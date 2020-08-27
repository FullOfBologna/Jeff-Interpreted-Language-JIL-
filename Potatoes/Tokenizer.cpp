#include "Tokenizer.h"

Tokenizer::Tokenizer()
	:
	m_tokenLUT(initializeTokenArray()),
	m_keywordLUT(initializeKeywordArray())
{

}

Tokenizer::~Tokenizer()
{

}

Token Tokenizer::generateToken(std::string input, bool isArgument)
{
	Token token;
	//Parse only number first, so it does not get stored as a variable

	stripSpaces(input);

	// std::cout << "{" << input << "}" << std::endl;

	auto iter = std::find(m_keywordLUT.begin(), m_keywordLUT.end(),input);

	if (iter != m_keywordLUT.end())
	{
		token = std::make_tuple(m_tokenLUT[7], input);
	}
	else if(isArgument)
	{
		token = std::make_tuple(m_tokenLUT[8], input);
	}else if (isNumber(input))
	{
		token = std::make_tuple(m_tokenLUT[2], input);
	}
	else if (isAlphaNumerical(input))
	{
		token = std::make_tuple(m_tokenLUT[0], input);
	}
	else if (input == "=")
	{
		token = std::make_tuple(m_tokenLUT[1], "=");
	}
	else if (input == "+")
	{
		token = std::make_tuple(m_tokenLUT[3], "+");
	}
	else if (input == "-")
	{
		token = std::make_tuple(m_tokenLUT[4], "-");
	}
	else if (input == "*")
	{
		token = std::make_tuple(m_tokenLUT[5], "*");
	}
	else if (input == "/")
	{
		token = std::make_tuple(m_tokenLUT[6], "/");
	}
	else
	{
		token = std::make_tuple(m_tokenLUT[4], ("Syntax Error: Unknown Command " + input));
	}

	return token;
}

TokenNameArray Tokenizer::initializeTokenArray()
{
	TokenNameArray newTokenArray;

	newTokenArray[0] = "NAME";
	newTokenArray[1] = "EQUALS";
	newTokenArray[2] = "NUMBER";
	newTokenArray[3] = "ADD";
	newTokenArray[4] = "SUB";
	newTokenArray[5] = "MULT";
	newTokenArray[6] = "DIV";
	newTokenArray[7] = "KEYWD";
	newTokenArray[8] = "ARG";
	newTokenArray[9] = "ERROR";

	return newTokenArray;
}

KeyWordArray Tokenizer::initializeKeywordArray()
{
	KeyWordArray keyWordArray;

	keyWordArray[0] = "print";
	keyWordArray[1] = "do";
	keyWordArray[2] = "while";
	keyWordArray[3] = "if";
	keyWordArray[4] = "else";
	keyWordArray[5] = "for";
	keyWordArray[6] = "break";
	keyWordArray[7] = "end";

	return keyWordArray;
}

void Tokenizer::stripSpaces(std::string& inputString)
{
	// std::cout << "InputSTRING = {" << inputString << "}" << std::endl;

	int i = 0;

	std::string s;

	for(int i = 0; i < inputString.length(); i++)
	{
		if(inputString[i] != ' ')
		{
			s.push_back(inputString[i]);
		}
	}

	inputString = s;

	// std::cout << "New Input String = {" << inputString << "}" << std::endl;
}

KeyWordArray Tokenizer::getKeywordArray()
{
	return m_keywordLUT;
}