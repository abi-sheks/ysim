#pragma once
#include <string>

enum Instruction
{
    HALT,
    NOP,
    RET,

    ADDQ,
    ANDQ,
    XORQ,
    SUBQ,

    RRMOVQ,
    CMOVLE,
    CMOVL,
    CMOVE,
    CMOVNE,
    CMOVGE,
    CMOVG,

    PUSHQ,
    POPQ,

    IRMOVQ,
    RMMOVQ,
    MRMOVQ,

    CALL,
    JMP,
    JLE,
    JL,
    JE,
    JNE,
    JGE,
    JG,

    INCORRECT
};

typedef std::pair<Instruction, std::string> typed_mi ;
class AddressedInstruction
{
    public:
    AddressedInstruction(long _addr, std::string _instr) : address(_addr), instr(_instr) {}
    long address;
    std::string instr;

};
