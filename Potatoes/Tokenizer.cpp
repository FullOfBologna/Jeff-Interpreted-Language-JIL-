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
	//Parse only number first, so it does not get stored as a variable

	stripSpaces(input);

	std::cout << "{" << input << "}" << std::endl;

	if (isNumber(input))
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
	newTokenArray[7] = "ERROR";

	return newTokenArray;
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