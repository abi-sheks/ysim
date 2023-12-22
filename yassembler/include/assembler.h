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
    Assembler(std::string filename);
    void assemble();
    void print_instructions();
    void print_machine_instructions();
};