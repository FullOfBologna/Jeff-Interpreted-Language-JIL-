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
    std::cout << "print() called. " << '\n';
    std::cout << inputString << '\n';
    //Interpret the string. 
    // for stored variables, check if the name exists, check if 
}

