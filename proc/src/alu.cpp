#include "../include/alu.h"
#include <climits>

// processing each of the two nibbles that come with each instruction specifier. one char == one nibble (0 to F)
std::string ALU::execute_instruction(char code_nib, char func_nib, word valA, word valB, word valC)
{
    // returns whatever valE is required, will later change condition codes
    // halt
    if (code_nib == '0')
        exit(1);
    // nop
    if (code_nib == '1')
        return "";
    // irmovq
    if (code_nib == '3' && func_nib == '0')
        return valC;
    // rmmovq and mrmovq
    if ((code_nib == '4' && func_nib == '0') || (code_nib == '5' && func_nib == '0'))
    {
        auto b_int = atoi(valB.c_str());
        auto c_int = atoi(valC.c_str());
        auto e_int = b_int + c_int;
        auto valE = itos(e_int);
        return zero_extend_hex(valE).substr(2);
    }
    // ops
    if (code_nib == '6')
    {
        auto a_int = atoi(valA.c_str());
        auto b_int = atoi(valB.c_str());
        size_t e_int;

        if (func_nib == '0')
            e_int = b_int + a_int;
        else if (func_nib == '1')
            e_int = b_int - a_int;
        else if (func_nib == '2')
            e_int = b_int & a_int;
        else if (func_nib == '3')
            e_int = b_int | a_int;
        else
            throw std::runtime_error("ERROR : Invalid operation");
        auto valE = itos(e_int);
        return zero_extend_hex(valE).substr(2);
    }
    // call and ret
    if ((code_nib == '8' && func_nib == '0') || (code_nib == '9' && func_nib == '0'))
    {
        auto multiplier = code_nib == '8' ? -1 : 1;
        size_t e_int = atoi(valB.c_str()) + (multiplier * 8);
        std::string valE = itos(e_int);
        return zero_extend_hex(valE).substr(2);
    }
    //push and pop
    if ((code_nib == 'A' && func_nib == '0') || (code_nib == 'B' && func_nib == '0'))
    {
        auto multiplier = code_nib == 'A' ? -1 : 1;
        size_t e_int = atoi(valB.c_str()) + (multiplier * 8);
        std::string valE = itos(e_int);
        return zero_extend_hex(valE).substr(2);
    }
}