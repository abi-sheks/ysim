#pragma once
#include "instruction.h"
#include <iomanip>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

typedef std::map<std::string, std::string> register_reference;
typedef std::map<std::string, Instruction> instruction_reference;
typedef std::map<Instruction, std::string> specifier_reference;
typedef std::map<Instruction, int> offset_map;

static const std::string REGISTER_FILE_NAME = "../registers.txt";
std::vector<std::string> split_at_whitespaces(std::string instr);
register_reference get_registers();
instruction_reference get_instr_to_enum();
specifier_reference get_codes();
specifier_reference get_function_specs();
offset_map get_offsets();
// will change to sign extend later
std::string zero_extend_hex(std::string number);