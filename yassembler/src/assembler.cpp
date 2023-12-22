#include "../include/assembler.h"
#include <stdexcept>
#include "../include/lexer.h"
#include "../include/parser.h"

Assembler::Assembler(std::string filename)
{
    std::ifstream file_handle;
    file_handle.open(filename);
    if (file_handle.is_open())
    {
        std::string sa;
        while (std::getline(file_handle, sa))
        {
            if (sa != "")
            {
                instructions.push_back(sa);
            }
        }
    }
    else
    {
        std::cout << "Error!" << "received filename is " << filename;
    }
}
void Assembler::assemble()
{
    // errors handled at this stage
    Lexer lexer;
    Parser parser;
    std::string base_address = "0";
    std::vector<std::vector<token>> all_tokens;
    // first pass
    for (auto &instruction : instructions)
    {
        try
        {
            auto tokens = lexer.tokenize(instruction);
            for (auto &token : tokens)
            {
                if (token.first == TokenType::INVALID)
                {
                    throw std::runtime_error("ERROR : Invalid syntax");
                }
            }
            // current address
            tokens.push_back(std::pair(TokenType::ADDRESS, base_address));
            // for second pass
            all_tokens.push_back(tokens);
            // first_parse will change base_address according to instruction
            // unless it is label, in which case address is untouched.
            auto machine_code = parser.first_parse(tokens, base_address);
            if (machine_code.first != Instruction::INCORRECT)
            {
                // labels generate no machine code
                machine_instructions.push_back(machine_code);
            }
        }
        catch(std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    for (auto &instruction : machine_instructions)
    {
        // perform second pass and fill out call and jump targets based on label mapping
        try
        {
        parser.resolve_targets(instruction);
        }
        catch(std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
void Assembler::print_instructions()
{
    for (auto &instruction : instructions)
    {
        std::cout << instruction << "\n";
    }
}
void Assembler::print_machine_instructions()
{
    for (auto &instruction : machine_instructions)
    {
        std::cout << instruction.second << "\n";
    }
}