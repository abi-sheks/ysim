#pragma once
#include <string>

class ALU
{
    public:
    ALU(){};
    std::string executeInstruction(std::string opcode);
};