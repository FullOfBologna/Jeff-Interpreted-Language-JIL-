#pragma once

#include <cstdint>

#include <array>
#include <vector>

#include "Defines.h"


typedef uint32_t Size;
typedef uint32_t Id;
typedef std::uint64_t Position;
typedef std::string Name;
typedef std::tuple<Name,std::string> Token;
typedef std::array<Name,TOKEN_NAME_COUNT> TokenNameArray;
typedef std::vector<Token> TokenList;