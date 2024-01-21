#pragma once
#include <iostream>
#include <vector>
#include "../../global/instruction.h"
#include "lexer.h"
#include "parser.h"
#include <fstream>

class Assembler
{
private:
    std::vector<std::string> instructions;

public:
    std::vector<typed_mi> machine_instructions;
    Assembler(std::string filename);
    void assemble();
    void print_instructions();
    void print_machine_instructions();
};