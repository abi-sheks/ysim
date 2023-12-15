#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

typedef std::pair<std::string, std::string> token;

// simply takes in an instruction and outputs a tokenized version
class Lexer
{
public:
    std::vector<token> tokenize(const std::string &instr)
    {
        std::vector<token> tokens;
        std::stringstream mystream(instr);
        std::string temp;
        char delim = ' ';
        while (std::getline(mystream, temp, delim))
        {
            if (temp[0] >= 97 && temp[0] <= 122)
            {
                if (temp[temp.length() - 1] == ':')
                {
                    tokens.push_back(std::pair("Label", temp.substr(0, temp.length() - 1)));
                }
                else
                {
                    tokens.push_back(std::pair("Identifier", temp));
                }
            }
            else if (temp[0] == '%')
            {
                auto reg_name = temp.substr(1, temp.length());
                tokens.push_back(std::pair("Register", reg_name));
            }
            else if (temp[0] == '$')
            {
                auto literal = temp.substr(1, temp.length());
                tokens.push_back(std::pair("Literal", literal));
            }
        }
        return tokens;
    }
};