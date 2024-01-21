#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "../../yassembler/include/assembler.h"

class InstructionMemory
{
    private:
    public:
    std::vector<std::string> instructions;
    InstructionMemory(Assembler &ass);
};