#pragma once

#include <string>
#include <sys/stat.h>

#include "CommonIncludes.h"

bool fileExists(const std::string& fileName);

bool isNumber(std::string);
bool isAlpha(std::string);
bool isAlphaNumerical(std::string);

Name getName(Token);
std::string getValue(Token);

