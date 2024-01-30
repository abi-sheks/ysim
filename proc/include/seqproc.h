#pragma once
#include "instr_mem.h"
#include "regfile.h"
#include "alu.h"
#include "cnd_flags.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "../../yassembler/include/assembler.h"
#include "../../global/utils.h"



class Processor
{
private:
    //helper
    std::string get_next_valp(int length, std::string current_addr);
    InstructionMemory *instr_memory;
    RegisterFile *register_file;
    ALU *alu;
    CndCodes*cnds;
    //all 8 bytees / 16 chars
    //all the words represent data in decimal format for now, will later make it so that they store hex 
    char icode;
    char ifun;
    char rA;
    char rB;
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
            register_file->initialize_registers();
            cnds = new CndCodes();
            //
            PC = "0000000000000000";
            rA = 'F';
            rB = 'F';
            icode = 'F';
            ifun = 'F';
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(1);
        }
    }
    void instruction_loop();
    void fetch();
    void decode();
    void execute();
    void memory();
    void write_back();
    void pc_update();
};