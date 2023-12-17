#pragma once
#include <string>
#include <utility>

enum TokenType
{
    TARGET,
    ADDRESS,
    IDENTIFIER,
    REGISTER, 
    LITERAL,
    LABEL,  
    INVALID
};
typedef std::pair<TokenType, std::string> token;
