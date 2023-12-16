#pragma once
#include "instruction.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

typedef std::map<std::string, std::string> register_reference;
typedef std::map<std::string, Instruction> instruction_reference;
typedef std::map<Instruction, std::string> specifier_reference;

const std::string REGISTER_FILE_NAME = "../registers.txt";

// enum tables
class EnumTables
{
public:
    EnumTables()
    {
        // instr_to_enum = {
        //     {"halt", Instruction::HALT},
        //     {"nop", Instruction::NOP},

        //     // operations (2reg)
        //     {"addq", Instruction::ADDQ},
        //     {"andq", Instruction::ANDQ},
        //     {"xorq", Instruction::XORQ},
        //     {"subq", Instruction::SUBQ},

        //     // moves and conditional moves(2reg)
        //     {"rrmovq", Instruction::RRMOVQ},
        //     {"cmovle", Instruction::CMOVLE},
        //     {"cmovl", Instruction::CMOVL},
        //     {"cmove", Instruction::CMOVE},
        //     {"cmovne", Instruction::CMOVNE},
        //     {"cmovge", Instruction::CMOVGE},
        //     {"cmovg", Instruction::CMOVG},
        // };
        // codes = {
        //     {Instruction::HALT, "0"},
        //     {Instruction::NOP, "1"},

        //     // operations (2reg)
        //     {Instruction::ADDQ, "6"},
        //     {Instruction::ANDQ, "6"},
        //     {Instruction::SUBQ, "6"},
        //     {Instruction::XORQ, "6"},

        //     // moves and conditional moves(2reg)
        //     {Instruction::RRMOVQ, "2"},
        //     {Instruction::CMOVLE, "2"},
        //     {Instruction::CMOVL, "2"},
        //     {Instruction::CMOVE, "2"},
        //     {Instruction::CMOVNE, "2"},
        //     {Instruction::CMOVGE, "2"},
        //     {Instruction::CMOVG, "2"},
        // };
        // function_specs = {
        //     {Instruction::HALT, "0"},
        //     {Instruction::NOP, "0"},

        //     // operations (2reg)
        //     {Instruction::ADDQ, "0"},
        //     {Instruction::ANDQ, "2"},
        //     {Instruction::SUBQ, "1"},
        //     {Instruction::XORQ, "3"},

        //     // moves and conditional moves(2reg)
        //     {Instruction::RRMOVQ, "0"},
        //     {Instruction::CMOVLE, "1"},
        //     {Instruction::CMOVL, "2"},
        //     {Instruction::CMOVE, "3"},
        //     {Instruction::CMOVNE, "4"},
        //     {Instruction::CMOVGE, "5"},
        //     {Instruction::CMOVG, "6"},
        // };
    }
};

std::vector<std::string> split_into_whitespaces(std::string instr)
{
    std::stringstream mystream(instr);
    std::string temp;
    std::vector<std::string> final;
    char delim = ' ';
    while (std::getline(mystream, temp, delim))
    {
        final.push_back(temp);
    }
    return final;
}

register_reference get_registers()
{
    register_reference result;
    std::ifstream file_handle;
    file_handle.open(REGISTER_FILE_NAME);
    std::string line;
    while (std::getline(file_handle, line))
    {
        auto reg_info = split_into_whitespaces(line);
        result.emplace(reg_info[0], reg_info[1]);
    }
    return result;
}

instruction_reference get_instr_to_enum()
{
    instruction_reference instr_to_enum;
    instr_to_enum = {
        {"halt", Instruction::HALT},
        {"nop", Instruction::NOP},

        // operations (2reg)
        {"addq", Instruction::ADDQ},
        {"andq", Instruction::ANDQ},
        {"xorq", Instruction::XORQ},
        {"subq", Instruction::SUBQ},

        // moves and conditional moves(2reg)
        {"rrmovq", Instruction::RRMOVQ},
        {"cmovle", Instruction::CMOVLE},
        {"cmovl", Instruction::CMOVL},
        {"cmove", Instruction::CMOVE},
        {"cmovne", Instruction::CMOVNE},
        {"cmovge", Instruction::CMOVGE},
        {"cmovg", Instruction::CMOVG},
    };
    return instr_to_enum;
}

specifier_reference get_codes()
{

    specifier_reference codes;
    codes = {
        {Instruction::HALT, "0"},
        {Instruction::NOP, "1"},

        // operations (2reg)
        {Instruction::ADDQ, "6"},
        {Instruction::ANDQ, "6"},
        {Instruction::SUBQ, "6"},
        {Instruction::XORQ, "6"},

        // moves and conditional moves(2reg)
        {Instruction::RRMOVQ, "2"},
        {Instruction::CMOVLE, "2"},
        {Instruction::CMOVL, "2"},
        {Instruction::CMOVE, "2"},
        {Instruction::CMOVNE, "2"},
        {Instruction::CMOVGE, "2"},
        {Instruction::CMOVG, "2"},
    };
    return codes;
}
specifier_reference get_function_specs()
{

    specifier_reference function_specs;
    function_specs = {
        {Instruction::HALT, "0"},
        {Instruction::NOP, "0"},

        // operations (2reg)
        {Instruction::ADDQ, "0"},
        {Instruction::ANDQ, "2"},
        {Instruction::SUBQ, "1"},
        {Instruction::XORQ, "3"},

        // moves and conditional moves(2reg)
        {Instruction::RRMOVQ, "0"},
        {Instruction::CMOVLE, "1"},
        {Instruction::CMOVL, "2"},
        {Instruction::CMOVE, "3"},
        {Instruction::CMOVNE, "4"},
        {Instruction::CMOVGE, "5"},
        {Instruction::CMOVG, "6"},
    };
    return function_specs;
}