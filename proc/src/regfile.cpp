#include "../include/regfile.h"
#include "../../global/utils.h"

void RegisterFile::initialize_registers()
{
    std::string line;
    std::ifstream reg_handle(REGISTER_FILE_NAME);
    int i = 0;
    while (std::getline(reg_handle, line))
    {
        auto reg_info = split_at_whitespaces(line);
        // known that reg_info[0] (code) is one character long
        if (reg_info[1].length() != 1)
        {
            throw std::runtime_error("ERROR : Registers file is invalid");
        }
        registers[i].set_code(reg_info[1][0]);
        registers[i].set_name(reg_info[0]);
        i++;
    }
}

std::string RegisterFile::read_from_register(char reg_code)
{
    for (int i = 0; i < 15; i++)
    {
        if (registers[i].get_code() == reg_code)
        {
            // match
            return registers[i].read_value();
        }
    }
    throw std::runtime_error("ERROR : Invalid register code");
}
void RegisterFile::write_to_register(std::string word, char reg_code)
{
    for (int i = 0; i < 15; i++)
    {
        if (registers[i].get_code() == reg_code)
        {
            // match
            registers[i].write_value(word);
            return;
        }
    }
    throw std::runtime_error("ERROR : Invalid register code");
}
