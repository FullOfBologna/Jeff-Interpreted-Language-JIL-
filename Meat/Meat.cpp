#include "Meat.h"

Meat::Meat():
	m_file(nullptr),
	m_output(""),
	m_potatoes(Potatoes()),
	m_lexy(Lexy(m_potatoes.getKeywordLUT()))
{

}

Meat::~Meat()
{
	delete m_file;
}

void Meat::setScript(const std::string& fileName)
{
	m_file = new JeffFile(fileName);
}

void Meat::readFile()
{
	std::uint16_t lineNumber(0);
	std::string readString;

	m_file->startReading();

	while (m_file->getLine(readString))
	{
		//std::cout << "Line " << lineNumber << ": " << readString << std::endl;

		//Interpret what the line is saying. 
		//
		//

		//Parse each non-whitespace character. 

		//Pass line in to Potato. Potato will parse, and tokenize the line. 
		// 
		//
		//

		m_potatoes.setLine(readString);

		TokenList tokenList = m_potatoes.parseLine();

		//for (auto& token : tokenList)
		//{
		//	std::cout << "Line: " << lineNumber << " ";
		//	printToken(token);
		//}

		m_lexy.setOverallTokenList(tokenList);

		//printASCII(readString);

		lineNumber++;

		if (lineNumber > 100)
		{
			break;
		}
	}
}

void Meat::printASCII(std::string& inputString)
{

	for (char& val : inputString)
	{
		std::cout << (int)val << " ";
	}
	std::cout << std::endl;
}


