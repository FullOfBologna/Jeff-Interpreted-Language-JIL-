#pragma once

#include "../Utils/CommonIncludes.h"
#include <map>
#include <regex>

class KeywordHandler
{
public:
    KeywordHandler(KeyWordArray inputKeywordArray);
    ~KeywordHandler();

    void setStoredVariables(std::map<std::string, float> storedVariables);
    void setKeyword(std::string inKeyword);
    void setArg(std::string inArg);

    void executeKeyword();
private:

    std::map<std::string, float> m_storedVariables;

    KeyWordArray m_keywordLUT;

    std::string m_currentKeyword;
    std::string m_currentArg;

    // Print will interpret the input string to determine what to print. 
    void printFunction(std::string inputArg);
    // void doFunction()
    ////////
    //  While Function will tell the file reading to go back to a certain line. 
    //
    // void whileFunction()
    // void ifHandler()

    ////////
    //  Break function will set the current line to one past the while function. 
    // void breakHandler();

  	bool isStored(std::string& var);
    void getMapValue(float&, std::string variableName);
};