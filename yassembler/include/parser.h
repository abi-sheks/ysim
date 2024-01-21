#pragma once
#include "../../global/instruction.h"
#include "../../global/utils.h"
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "token.h"

class Parser
{
public:
    Parser() {}
    void print_jump_table();
    void resolve_targets(typed_mi &mcode);
    typed_mi first_parse(std::vector<token> instr_token, std::string &curr_address);

private:
    std::map<std::string, std::string> jump_table;
    Instruction get_instruction(token token);
    bool check_syntax(Instruction instr, std::vector<token> tokens);
    std::string translate_to_machine(Instruction instr, std::vector<token> tokens);
    std::string get_register_code(token reg_token, Instruction instr);
    std::string compute_next_address(Instruction instr, std::string current_address);
};