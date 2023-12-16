#pragma once
#include <iostream>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include <fstream>

class Assembler
{
private:
    std::vector<std::string> instructions;
    std::vector<std::string> machine_instructions;

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
        for (auto &instruction : instructions)
        {
            try
            {
                auto tokens = lexer.tokenize(instruction);
                auto machine_code = parser.parse(tokens);
                machine_instructions.push_back(machine_code);
            }
            catch (std::string error)
            {
                std::cerr << error << '\n';
            }
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
            std::cout << instruction << "\n";
        }
    }
};