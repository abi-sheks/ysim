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
    char get_code() {return code;}
    std::string get_name() {return name;}
    std::string read_value() {return value;}
    void write_value(std::string word) {value = word;}
};