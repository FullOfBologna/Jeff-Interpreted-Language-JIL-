#pragma once
// Lexical Analyzer to execute a received Token List. 

#include "CommonIncludes.h"
#include <sstream>
#include <iostream>
#include <map>

class Lexy
{
public:
	Lexy();
	~Lexy();

	//Do I break the token down into a list of executable functions with proper 

	void setOverallTokenList(TokenList);

private:
	std::map<std::string,float> m_storedVariables;
	TokenList m_inputTokenList;

	enum Instructions
	{
		ADD,
		SUB,
		MULT,
		DIV,
		STORE,
		ERROR
	};

	bool isStored(std::string varName);

	void storeVariable(std::string varName);
	void updateMapValue(std::string, float);

	void printStoredVariables();

	/// <summary>
	/// This will be the big one. The logic will admittedly get nasty before it can be refined. 
	/// </summary>
	void executeAnalyzedInstructions();


};

