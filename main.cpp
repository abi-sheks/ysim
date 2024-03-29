#include "./yassembler/include/assembler.h"
#include "./proc/include/seqproc.h"
// #include "./mem/include/utilities.h"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "ERROR : proper number of arguments not specified";
        return -1;
    }
    Assembler assembler = Assembler(std::string(argv[1]));
    assembler.assemble();
    assembler.print_machine_instructions();
    //fill out instruction memory with assembled instruction
    Processor pprocessor(assembler);
    pprocessor.instruction_loop();
    pprocessor.exreg();
    return 0;
}