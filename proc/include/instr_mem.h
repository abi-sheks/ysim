#pragma once
#include <map>
#include <string>
#include <algorithm>
#include "../../yassembler/include/assembler.h"

class InstructionMemory
{
    private:
    public:
    std::map<std::string, std::string> instructions;
    InstructionMemory(Assembler &ass);
    
};