#pragma once
#include "token.h"
#include "utilities.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
// simply takes in an instruction and outputs a tokenized version
class Lexer
{
public:
    std::vector<token> tokenize(const std::string &instr)
    {
        std::vector<token> tokens;
        std::vector<std::string> words = split_into_whitespaces(instr);
        for (auto &temp : words)
        {
            if (temp[0] >= 97 && temp[0] <= 122)
            {
                if (temp[temp.length() - 1] == ':')
                {
                    tokens.push_back(std::pair(TokenType::LABEL, temp.substr(0, temp.length() - 1)));
                }
                else
                {
                    tokens.push_back(std::pair(TokenType::IDENTIFIER, temp));
                }
            }
            else if (temp[0] == '%')
            {
                auto reg_name = temp.substr(1, temp.length());
                tokens.push_back(std::pair(TokenType::REGISTER, reg_name));
            }
            else if (temp[0] == '$')
            {
                auto literal = temp.substr(1, temp.length());
                tokens.push_back(std::pair(TokenType::LITERAL, literal));
            }
            else
            {
                tokens.push_back(std::pair(TokenType::INVALID, ""));
            }
        }
        return tokens;
    }
};