#pragma once
#include <vector>
#include "../../global/utils.h"
#include "reg.h"
#include <fstream>
#include <sstream>

class RegisterFile
{
private:
    Register registers[15]; 

public:
    RegisterFile(){};
    void initialize_registers();
    //assuming 8 byte register values (will store as long in the future)
    std::string read_from_register(char reg_code);
    void write_to_register(std::string word, char reg_code);
};