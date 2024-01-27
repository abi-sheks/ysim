#pragma once
#include "instr_mem.h"
#include "regfile.h"
#include "alu.h"
#include "cnd_flags.h"
#include "../../yassembler/include/assembler.h"



class Processor
{
private:
    InstructionMemory *instr_memory;
    RegisterFile *register_file;
    ALU *alu;
    CndCodes*cnds;
    //all 8 bytees / 16 chars
    char icode;
    char ifun;
    word valA;
    word PC;
    word valM;
    word valE;
    word valB;
    word valC;
    word valP;
    // condition codes

public:
    Processor(Assembler &ass)
    {
        try
        {
            instr_memory = new InstructionMemory(ass);
            alu = new ALU();
            register_file = new RegisterFile();
            cnds = new CndCodes();
            //
            PC = "0000000000000000";
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(1);
        }
    }
    void instruction_loop();
    std::string fetch();
    void decode();
    void execute();
    void memory();
    void write_back();
};