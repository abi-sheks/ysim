#pragma once
#include "token.h"
#include "instruction.h"
#include "utilities.h"
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