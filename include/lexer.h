#pragma once
#include "token.h"
#include "instruction.h"
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
            
            //these cleanly send a [identifier][literal][register] to parser
            else if (temp[0] >= 48 && temp[0] <= 57)
            {
                // only format allowed is D(rA)
                if (temp.size() < 1)
                {
                    // invalid, wont assemble
                    tokens.push_back(std::pair(TokenType::INVALID, ""));
                    return tokens;
                }
                tokens.push_back(std::pair(TokenType::LITERAL, temp.substr(0, 1)));
                // check proper syntax and extract register specifier
                // some of this can be done on parsing, im throwing them here to simplify parsing job
                // doing these checks here simplifies what goes to parsing
                auto bracketed_term = temp.substr(1, temp.length());
                if (bracketed_term.length() != 5 && bracketed_term.length() != 6)
                {
                    tokens.push_back(std::pair(TokenType::INVALID, ""));
                    return tokens;
                }
                if (bracketed_term[0] != '(' || bracketed_term[bracketed_term.length() - 1] != ')' || bracketed_term[1] != '%')
                {
                    tokens.push_back(std::pair(TokenType::INVALID, ""));
                    return tokens;
                }
                auto reg_term = bracketed_term.substr(2, bracketed_term.length() - 3);
                tokens.push_back(std::pair(TokenType::REGISTER, reg_term));
            }
            else if (temp[0] == '(')
            {
                tokens.push_back(std::pair(TokenType::LITERAL, "1"));
                if (temp.length() != 5 && temp.length() != 6)
                {
                    tokens.push_back(std::pair(TokenType::INVALID, ""));
                    return tokens;
                }
                if (temp[0] != '(' || temp[temp.length() - 1] != ')' || temp[1] != '%')
                {
                    tokens.push_back(std::pair(TokenType::INVALID, ""));
                    return tokens;
                }
                auto reg_term = temp.substr(2, temp.length() - 3);
                tokens.push_back(std::pair(TokenType::REGISTER, reg_term));
            }
            else
            {
                // invalid, wont assemble
                tokens.push_back(std::pair(TokenType::INVALID, ""));
                return tokens;
            }
        }
        return tokens;
    }
};