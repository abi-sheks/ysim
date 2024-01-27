#include "../include/seqproc.h"


void Processor::instruction_loop()
{
    for(int i = 0; i < instr_memory->instructions.size(); i++)
    {
        std::string current_instr = fetch();
    }
}

std::string Processor::fetch()
{
    auto instruction = instr_memory->instructions[PC];
    
}
void Processor::execute()
{

}