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
    // condition codes
    char icode;
    char ifun;
    char rA;
    char rB;
    //all 8 bytes / 16 chars
    //all the words represent data in decimal format for now, will later make it so that they store hex 
    word valA;
    word PC;
    word valM;
    word valE;
    word valB;
    word valC;
    word valP;
    //for now, main memory is implemented as a map of strings to strings.
    //proper cache integration in another life, maybe.
    std::map<word, word> main_memory;

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
    void exreg();
    void exmem(word location) { std::cout << "At location : " << location << " -> " << main_memory[location] << "\n";}
};