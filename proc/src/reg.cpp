#include "../include/reg.h"

Register::Register(std::string name, char code)
{
    name = name;
    code = code;
    //initialising at 0
    value = '0000000000000000';
}