#include "utils.h"

std::vector<std::string> split_at_whitespaces(std::string instr)
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
        auto reg_info = split_at_whitespaces(line);
        result.emplace(reg_info[0], reg_info[1]);
    }
    return result;
}

// quick and shitty solution
register_reference get_registers_for_file()
{
    register_reference result;
    std::ifstream file_handle;
    file_handle.open(REGISTER_FILE_NAME);
    std::string line;
    while (std::getline(file_handle, line))
    {
        auto reg_info = split_at_whitespaces(line);
        // reverse because while processing we'll refer to the registers by their code
        result.emplace(reg_info[1], reg_info[0]);
    }
    return result;
}

instruction_reference get_instr_to_enum()
{
    instruction_reference instr_to_enum;
    instr_to_enum = {
        {"halt", Instruction::HALT},
        {"nop", Instruction::NOP},
        {"ret", Instruction::RET},

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

        // stack ops (1reg)
        {"pushq", Instruction::PUSHQ},
        {"popq", Instruction::POPQ},

        // immediate to register (1 reg, 1 constant word)
        {"irmovq", Instruction::IRMOVQ},

        // memory <-> register (2 reg, 1 constant word)
        {"rmmovq", Instruction::RMMOVQ},
        {"mrmovq", Instruction::MRMOVQ},

        // call/jump (no reg, 1 constant word)
        {"call", Instruction::CALL},
        {"jmp", Instruction::JMP},
        {"jle", Instruction::JLE},
        {"jl", Instruction::JL},
        {"je", Instruction::JE},
        {"jne", Instruction::JNE},
        {"jge", Instruction::JGE},
        {"jg", Instruction::JG},
    };
    return instr_to_enum;
}

specifier_reference get_codes()
{

    specifier_reference codes;
    codes = {
        {Instruction::HALT, "0"},
        {Instruction::NOP, "1"},
        {Instruction::RET, "9"},

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

        // stack ops (1reg)
        {Instruction::PUSHQ, "A"},
        {Instruction::POPQ, "B"},

        // immediate to register (1 reg, 1 constant word)
        {Instruction::IRMOVQ, "3"},

        // memory <-> register (2 reg, 1 constant word)
        {Instruction::RMMOVQ, "4"},
        {Instruction::MRMOVQ, "5"},

        // call/jump (no reg, 1 constant word)
        {Instruction::CALL, "8"},
        {Instruction::JMP, "7"},
        {Instruction::JLE, "7"},
        {Instruction::JL, "7"},
        {Instruction::JE, "7"},
        {Instruction::JNE, "7"},
        {Instruction::JGE, "7"},
        {Instruction::JG, "7"},

    };
    return codes;
}
specifier_reference get_function_specs()
{

    specifier_reference function_specs;
    function_specs = {
        {Instruction::HALT, "0"},
        {Instruction::NOP, "0"},
        {Instruction::RET, "0"},

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

        // stack ops (1reg)
        {Instruction::PUSHQ, "0"},
        {Instruction::POPQ, "0"},

        // immediate to register (1 reg, 1 constant word)
        {Instruction::IRMOVQ, "0"},

        // memory <-> register (2 reg, 1 constant word)
        {Instruction::RMMOVQ, "0"},
        {Instruction::MRMOVQ, "0"},

        // call/jump (no reg, 1 constant word)
        {Instruction::CALL, "0"},
        {Instruction::JMP, "0"},
        {Instruction::JLE, "1"},
        {Instruction::JL, "2"},
        {Instruction::JE, "3"},
        {Instruction::JNE, "4"},
        {Instruction::JGE, "5"},
        {Instruction::JG, "6"},
    };
    return function_specs;
}

offset_map get_offsets()
{
    offset_map offsets;
    // 1 byte = +8
    offsets = {
        {Instruction::HALT, 8},
        {Instruction::NOP, 8},
        {Instruction::RET, 8},

        // operations (2reg)
        {Instruction::ADDQ, 16},
        {Instruction::ANDQ, 16},
        {Instruction::SUBQ, 16},
        {Instruction::XORQ, 16},

        // moves and conditional moves(2reg)
        {Instruction::RRMOVQ, 16},
        {Instruction::CMOVLE, 16},
        {Instruction::CMOVL, 16},
        {Instruction::CMOVE, 16},
        {Instruction::CMOVNE, 16},
        {Instruction::CMOVGE, 16},
        {Instruction::CMOVG, 16},

        // stack ops (1reg)
        {Instruction::PUSHQ, 16},
        {Instruction::POPQ, 16},

        // immediate to register (1 reg, 1 constant word)
        {Instruction::IRMOVQ, 80},

        // memory <-> register (2 reg, 1 constant word)
        {Instruction::RMMOVQ, 80},
        {Instruction::MRMOVQ, 80},

        // call/jump (no reg, 1 constant word)
        {Instruction::CALL, 72},
        {Instruction::JMP, 72},
        {Instruction::JLE, 72},
        {Instruction::JL, 72},
        {Instruction::JE, 72},
        {Instruction::JNE, 72},
        {Instruction::JGE, 72},
        {Instruction::JG, 72},
    };
    return offsets;
}

// will change to sign extend later
std::string zero_extend_hex(std::string number)
{
    std::stringstream to_int;
    int num = 0;
    to_int << number;
    to_int >> num;
    std::stringstream to_hex;
    to_hex << "0x"
           // one character represents one nibble, so for 8 bytes, 16 characters
           << std::setfill('0') << std::setw(sizeof(int) * 4)
           << std::hex << num;
    return to_hex.str();
}

std::string itos(int val)
{
    std::stringstream to_string;
    std::string valstr;
    to_string << val;
    to_string >> valstr;
    return valstr;
}
