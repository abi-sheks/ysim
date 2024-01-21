#include "../include/instr_mem.h"

InstructionMemory::InstructionMemory(Assembler &ass)
{
    for (int i = 0; i < ass.machine_instructions.size(); i++)
    {
        std::string instr = ass.machine_instructions[i].second;
        // instruction is printed as 0x<8 length address> 0x <actual instruction>
        int actual_instr_start = 2 + (2 * sizeof(int)) + 1 + 2 + 1;
        auto act_instr = instr.substr(actual_instr_start);
        //stripping whitespace
        std::string::iterator end_pos = std::remove(act_instr.begin(), act_instr.end(), ' ');
        act_instr.erase(end_pos, act_instr.end());
        instructions.push_back(act_instr);
    }
}