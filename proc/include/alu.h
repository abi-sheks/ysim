#pragma once
#include <string>
#include "../../global/utils.h"

class ALU
{
    public:
    ALU(){};
    std::string execute_instruction(char code_byte, char func_byte, word valA, word valB, word valC);
};