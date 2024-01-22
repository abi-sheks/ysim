#pragma once
#include "instr_mem.h"
#include "regfile.h"
#include "alu.h"
#include "../../yassembler/include/assembler.h"



class Processor
{
private:
    InstructionMemory *instr_memory;
    RegisterFile *register_file;
    ALU *alu;
    //all 8 bytees / 16 chars
    word valA;
    word PC;
    word valM;
    word valE;
    word valA;
    word valB;
    word valC;
    word valP;
public:
    Processor(Assembler &ass)
    {
        try
        {
            instr_memory = new InstructionMemory(ass);
            alu = new ALU();
            register_file = new RegisterFile();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(1);
        }
    }
    void fetch();
    void decode();
    void execute();
    void memory();
    void write_back();
};