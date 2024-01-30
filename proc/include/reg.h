#pragma once
#include <string>

class Register
{
private:
    char code;
    std::string name;
    std::string value;

public:
    Register()
    {
        name = "";
        code = 'F';
        value = "";
    }
    Register(std::string name, char code);
    char get_code() { return code; }
    void set_code(char i_code) {code = i_code;}
    void set_name(std::string i_name) {name = i_name;}
    std::string get_name() { return name; }
    std::string read_value() { return value; }
    void write_value(std::string word) { value = word; }
};