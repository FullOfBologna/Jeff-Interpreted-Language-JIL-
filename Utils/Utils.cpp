#include "Utils.h"

//Work around MSFT specific error. 
#pragma warning(disable:4996)

bool fileExists(const std::string& fileName)
{
	bool fileExists = false;
	FILE* file = fopen(fileName.c_str(), "r");
	if (!ferror(file))
	{
		fclose(file);
			fileExists = true;
	}
	else
	{
		fileExists = false;
	}

	return fileExists;
}

bool isNumber(std::string input)
{
	for (auto& val : input)
	{
		if (!std::isdigit(static_cast<int>(val)))
		{
			return false;
		}
	}

	return true;
}

bool isAlpha(std::string input)
{
	for (auto& val : input)
	{
		if (!std::isalpha(val))
		{
			return false;
		}
	}
	return true;
}

bool isAlphaNumerical(std::string input)
{
	for (auto& val : input)
	{
		std::string valString(&val);

		if (!isNumber(valString))
		{
			if (!isAlpha(valString))
			{
				return false;
			}
		}
	}
	return true;
}

Name getName(Token token)
{
	return std::get<0>(token);
}

std::string getValue(Token token)
{
	return std::get<1>(token);
}

void printToken(Token token)
{
	Name name = std::get<0>(token);
	std::string value = std::get<1>(token);

	std::cout << "Token Name: " << name << ", Value: " << value << '\n';
}