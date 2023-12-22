#include "../include/lexer.h"

std::vector<token> Lexer::tokenize(const std::string &instr)
    {
        std::vector<token> tokens;
        std::vector<std::string> words = split_at_whitespaces(instr);
        if (words[0][0] >= 97 && words[0][0] <= 122)
        {
            if (words[0][words[0].length() - 1] == ':')
            {
                tokens.push_back(std::pair(TokenType::LABEL, words[0].substr(0, words[0].length() - 1)));
            }
            else
            {
                tokens.push_back(std::pair(TokenType::IDENTIFIER, words[0]));
            }
        }
        auto words_non_ident = std::vector<std::string>(words.begin() + 1, words.end());
        for (auto &temp : words_non_ident)
        {
            if (temp[0] >= 97 && temp[0] <= 122)
            {
                //target name pushed here for call and jmp, actual address will always be at the end of the vector.
                tokens.push_back(std::pair(TokenType::TARGET, temp));
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

            // these cleanly send a [identifier][literal][register] to parser
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