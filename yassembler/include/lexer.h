#pragma once
#include "token.h"
#include "../../global/instruction.h"
#include "../../global/utils.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
// simply takes in an instruction and outputs a tokenized version
class Lexer
{
public:
    std::vector<token> tokenize(const std::string &instr);
};