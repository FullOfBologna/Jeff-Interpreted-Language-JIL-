#pragma once
// Lexical Analyzer to execute a received Token List. 

#include "../Utils/CommonIncludes.h"
#include <sstream>
#include <iostream>
#include <map>
#include <deque>

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
	void getMapValue(float& value, std::string var);
	
	bool getOperatorValues(float* floatArray, uint32_t iterator);

	void printStoredVariables();

	bool findMathOperators(std::deque<int>&, TokenList& tokenList);
	bool findEqualsOperator(std::deque<int>&, TokenList& tokenList);

	bool findMultDivOps(std::deque<int>&, TokenList& tokenList);
	bool findAddSubOps(std::deque<int>&, TokenList& tokenList);

	/// <summary>
	/// This will be the big one. The logic will admittedly get nasty before it can be refined. 
	/// </summary>
	bool executeAnalyzedInstructions(TokenList tokenList);

	bool newExecutor(TokenList tokenList);

	bool checkIfStored(std::string& var);

	bool performArithmetic(TokenList& IOTokenList);
	bool performLogic(TokenList& inputTokenList);
};

