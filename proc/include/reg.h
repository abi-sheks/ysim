#pragma once
#include <string>

class Register
{
    private:
    char code;
    std::string name;
    std::string value;

    public:
    Register(std::string name, char code);
};