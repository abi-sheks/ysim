#pragma once
#include "instr_mem.h"
#include "regfile.h"
#include "alu.h"
#include "../../yassembler/include/assembler.h"

class PipelinedProcessor
{
    private:
    InstructionMemory*instr_memory;
    RegisterFile*register_file;
    ALU*alu;
    public:
    PipelinedProcessor(Assembler &ass)
    {
        instr_memory = new InstructionMemory(ass);
        alu = new ALU();
        register_file = new RegisterFile();
    }
};