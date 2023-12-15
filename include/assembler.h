#pragma once
#include <iostream>
#include <vector>
#include "lexer.h"
#include <fstream>

class Assembler
{
private:
    std::vector<std::string> instructions;

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
        Lexer lexer;
        for (auto &instruction : instructions)
        {
            auto tokens = lexer.tokenize(instruction);
            for (auto &token : tokens)
            {
                std::cout << token.first << " : " << token.second << " ";
            }
            std::cout << std::endl;
        }
    }
    void print_instructions()
    {
        for (auto &instruction : instructions)
        {
            std::cout << instruction << "\n";
        }
    }
};