#include "../include/seqproc.h"

void Processor::instruction_loop()
{
    for (int i = 0; i < instr_memory->instructions.size(); i++)
    {
        // resets all flags for next instruction, no issue as not pipelined.
        cnds->reinitialize();
        fetch();
        decode();
        execute();
        memory();
        write_back();
        pc_update();
    }
}

void Processor::fetch()
{
    auto instruction = instr_memory->instructions[PC];
    if (instruction.length() < 2)
        throw std::runtime_error("ERROR::Invalid instruction encountered at fetch stage::invalid size of instruction");
    icode = instruction[0];
    ifun = instruction[1];
    // will have to repeat the get_next_valp call in every if statement because of the pattern im using
    // the function updates state so cant just haphazardly call it outside the ifs. the whole function is not atomic so have to be careful with
    // state
    if (instruction.length() == 2)
    {
        // nop, halt or ret expected
        if (icode == '0' && ifun == '0')
        {
            valP = get_next_valp(instruction.length(), PC);
            exit(1);
        }
        if (icode == '1' && ifun == '0')
        {
            valP = get_next_valp(instruction.length(), PC);
            return;
        }
        if (icode == '9' && ifun == '0')
        {
            valP = get_next_valp(instruction.length(), PC);
            return;
        }
    }
    if (instruction.length() == 4)
    {
        // cmovqs, opqs, stackopqs
        if ((icode == '2' && ((int)ifun >= 48 && (int)ifun <= 54)) || (icode == '6' && (ifun >= 48 && ifun <= 51)) || ((icode == 'A' || icode == 'B') && ifun == '0'))
        {
            valP = get_next_valp(instruction.length(), PC);
            rA = instruction[2];
            rB = instruction[3];
            return;
        }
    }
    if (instruction.length() == 18)
    {
        // jmp and call
        if (icode == '7' && ((int)ifun >= 48 && (int)ifun <= 54) || icode == '8' && ifun == '0')
        {
            valP = get_next_valp(instruction.length(), PC);
            valC = instruction.substr(2);
            return;
        }
    }
    if (instruction.length() == 20)
    {
        // irmovq, rmmovq and mrmovq expected
        if ((icode == '3' || icode == '4' || icode == '5') && ifun == '0')
        {
            valP = get_next_valp(instruction.length(), PC);
            rA = instruction[2];
            rB = instruction[3];
            valC = instruction.substr(4);
            return;
        }
    }
    throw std::runtime_error("ERROR : Invalid instruction encountered at fetch stage");
}
void Processor::decode()
{
    auto register_codes = get_registers();
    // as it is run sequentially after fetch, discarding unneeded checks on ifun
    if (icode == '0' || icode == '1' || icode == '3' || icode == '7')
        return;
    if (icode == '2')
    {
        valA = register_file->read_from_register(rA);
    }
    if (icode == '4' || icode == '6')
    {
        valA = register_file->read_from_register(rA);
        valB = register_file->read_from_register(rB);
    }
    if (icode == '5')
        valB = register_file->read_from_register(rB);
    if (icode == '8')
        valB = register_file->read_from_register(register_codes["rsp"][0]);
    if (icode == '9' || icode == 'B')
    {
        auto rsp_val = register_file->read_from_register(register_codes["rsp"][0]);
        valA = rsp_val;
        valB = rsp_val;
    }
    if (icode == 'A')
    {
        valA = register_file->read_from_register(rA);
        valB = register_file->read_from_register(register_codes["rsp"][0]);
    }
}

void Processor::execute()
{
    valE = alu->execute_instruction(icode, ifun, valA, valB, valC, *cnds);
}

void Processor::memory()
{

}
void Processor::write_back()
{
    auto register_codes = get_registers();
    if (icode == '1' || icode == '0' || icode == '4' || icode == '7')
        return;
    if (icode == '2' || icode == '3' || icode == '6')
    {
        register_file->write_to_register(valE, rB);
    }
    if (icode == '5')
        register_file->write_to_register(valM, rA);
    if (icode == '8' || icode == '9' || icode == 'A')
        register_file->write_to_register(valE, register_codes["rsp"][0]);
    if (icode == 'B')
    {
        register_file->write_to_register(valE, register_codes["rsp"][0]);
        register_file->write_to_register(valM, rA);
    }
}

void Processor::pc_update()
{
    if (icode == '1' || icode == '2' || icode == '3' || icode == '4' || icode == '5' || icode == '6' || icode == 'A' || icode == 'B')
    {
        PC = valP;
    }
    if (icode == '8')
        PC = valC;
    if (icode == '9')
        PC = valM;
    if (icode == '7')
    {
        PC = cnds->get_cnd() ? valC : valP;
    }
}

std::string Processor::get_next_valp(int length, std::string current_addr)
{
    unsigned int addr_int = 0;
    std::stringstream to_int;
    to_int << current_addr;
    to_int >> addr_int;
    auto new_valp = addr_int + (4 * length);
    std::string res;
    std::stringstream to_string;
    to_string << new_valp;
    to_string >> res;
    // omitting 0x
    return zero_extend_hex(res).substr(2);
}