#include "Tokenizer.h"

Tokenizer::Tokenizer()
	:
	m_tokenLUT(initializeTokenArray())
{

}

Tokenizer::~Tokenizer()
{

}

Token Tokenizer::generateToken(std::string input)
{
	Token token;
	if (isAlphaNumerical(input))
	{
	token = std::make_tuple(m_tokenLUT[0], input);
	}
	else if (input == "=")
	{
		token = std::make_tuple(m_tokenLUT[1], "=");
	}
	else if (isNumber(input))
	{
		token = std::make_tuple(m_tokenLUT[2], input);
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
	newTokenArray[4] = "MINUS";
	newTokenArray[5] = "MULT";
	newTokenArray[6] = "DIV";
	newTokenArray[7] = "ERROR";

	return newTokenArray;
}
