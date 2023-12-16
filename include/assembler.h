#pragma once
#include <iostream>
#include <vector>
#include "instruction.h"
#include "lexer.h"
#include "parser.h"
#include <fstream>

class Assembler
{
private:
    std::vector<std::string> instructions;
    std::vector<typed_mi> machine_instructions;

public:
    Assembler(std::string filename)
    {
        std::ifstream file_handle;
        file_handle.open(filename);
        if (file_handle.is_open())
        {
            std::string sa;
            while (std::getline(file_handle, sa))
            {
                if (sa != "")
                {
                    instructions.push_back(sa);
                }
            }
        }
    }
    void assemble()
    {
        // errors handled at this stage
        Lexer lexer;
        Parser parser;
        std::string base_address = "0";
        std::vector<std::vector<token>> all_tokens;
        //first pass
        for (auto &instruction : instructions)
        {
            try
            {
                auto tokens = lexer.tokenize(instruction);
                for(auto& token : tokens)
                {
                    if(token.first == TokenType::INVALID)
                    {
                        throw "ERROR : Invalid syntax";
                    }
                }
                // base address for all
                tokens.push_back(std::pair(TokenType::ADDRESS, base_address));
                //for second pass
                all_tokens.push_back(tokens);
                //first_parse will change base_address according to instruction
                auto machine_code = parser.first_parse(tokens, base_address);
                machine_instructions.push_back(machine_code);
            }
            catch (std::string error)
            {
                std::cerr << error << '\n';
            }
        }
        for(auto &instruction : machine_instructions)
        {
            //perform second pass and fill out call and jump targets based on label mapping
        }
    }
    void print_instructions()
    {
        for (auto &instruction : instructions)
        {
            std::cout << instruction << "\n";
        }
    }
    void print_machine_instructions()
    {
        for (auto &instruction : machine_instructions)
        {
            std::cout << instruction.second << "\n";
        }
    }
};