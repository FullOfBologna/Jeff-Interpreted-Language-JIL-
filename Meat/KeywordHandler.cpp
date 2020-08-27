#include "KeywordHandler.h"

KeywordHandler::KeywordHandler(KeyWordArray inputKeyword)
: m_keywordLUT(inputKeyword)
{

}

KeywordHandler::~KeywordHandler()
{

}

void KeywordHandler::setStoredVariables(std::map<std::string, float> inputStoredVariables)
{
    m_storedVariables = inputStoredVariables;
}

void KeywordHandler::setKeyword(std::string inKeyword)
{
    m_currentKeyword = inKeyword;
}

void KeywordHandler::setArg(std::string inArg)
{
    m_currentArg = inArg;
}

void KeywordHandler::executeKeyword()
{
    for(auto keyword : m_keywordLUT)
    {
        if(m_currentKeyword == keyword)
        {
            if(m_currentKeyword == "print")
            {
                printFunction(m_currentArg);
            }
        }
    }
}

void KeywordHandler::printFunction(std::string inputString)
{
    //Compare Input string with stored variables. 

    //Interpret the string. 
    // for stored variables, check if the name exists, check if 

    //Have a regEx that splits the input string into the quoted string, and the 

    std::string regExString = "\"(.*)\"\\s*\\+\\s*(.*)";
    std::regex rExp(regExString);

    std::smatch m;

	std::regex_search(inputString, m, rExp);

    for(int i = 1; i < m.size(); i++)
    {
        std::string var = m[i].str();
        if(isStored(var))
        {
            float varValue;
            getMapValue(varValue, var);
            // std::cout << "Found stored Variable: " << m[i] << ": " << varValue << '\n';
            std::cout << varValue ;
        }
        else
        {
            std::cout << m[i] << " ";
        }
    }

    std::cout << '\n';
}

bool KeywordHandler::isStored(std::string& varName)
{
	auto iterator = m_storedVariables.find(varName);
	if (iterator == m_storedVariables.end())
		return false;
	return true;
}

void KeywordHandler::getMapValue(float& outputFloat, std::string variableName)
{
	outputFloat = m_storedVariables.find(variableName)->second;
}