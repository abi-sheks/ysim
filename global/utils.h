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
//will refactor to long later. expected to have 8 bytes i.e 16 characters
typedef std::string word;

static const std::string REGISTER_FILE_NAME = "/root/ysim/registers.txt";
std::vector<std::string> split_at_whitespaces(std::string instr);
register_reference get_registers();
register_reference get_registers_for_file();
instruction_reference get_instr_to_enum();
specifier_reference get_codes();
specifier_reference get_function_specs();
offset_map get_offsets();
std::string itos(int val);
// will change to sign extend later
std::string zero_extend_hex(std::string number);