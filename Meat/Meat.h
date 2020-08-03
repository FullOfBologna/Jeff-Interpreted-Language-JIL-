#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include "../FileReading/JeffFile.h"

#include "../Potatoes/Potatoes.h"
#include "Lexy.h"

//Meat of the interpreter. 
class Meat
{
public:
	Meat();
	~Meat();

	void setScript(const std::string& fileName);

	void readFile();

private:

	void printASCII(std::string& inputString);
	void printToken(Token);
	void parseLine();
	void executeTokenList(TokenList);

	JeffFile *m_file;

	Potatoes m_potatoes;
	Lexy m_lexy;
	std::string m_output;
};

