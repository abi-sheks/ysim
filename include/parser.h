#pragma once
#include "instruction.h"
#include <iostream>
#include <vector>

enum TokenType;

class Parser
{
public:
    Parser() {}
    std::string parse(std::vector<token> instr_token)
    {
        // given a stream of tokens, the first token must be either an identifier or a label
        // parser will look up syntax according to identifier and verify, then translate to machine code.
        // first check_syntax()
        // second translate()
        std::string instructions = "";
        if (instr_token[0].first == TokenType::INVALID || instr_token[0].first == TokenType::REGISTER || instr_token[0].first == TokenType::LITERAL)
        {
            throw "FAILED : Incorrect instruction encountered";
        }
        if (instr_token[0].first == TokenType::LABEL)
        {
            // there can be no other args
            if (instr_token.size() != 1)
            {
                throw "FAILED : Incorrect instruction encountered";
            }
            // logic to add label to symbol table
        }
        if (instr_token[0].first == TokenType::IDENTIFIER)
        {
            // perform lookup and verify syntax
            // lookup returns instruction name, and translation occurs according to instruction name
            try
            {
                Instruction gen_instr = get_instruction(instr_token[0]);
                if (gen_instr == Instruction::INCORRECT)
                    throw "ERROR : Invalid instruction";

                if (!check_syntax(gen_instr, instr_token))
                {
                    throw "ERROR : Invalid instruction";
                }
                auto machine_instr = translate_to_machine(gen_instr, instr_token);
                instructions.append(machine_instr);
            }
            catch (std::string error)
            {
                // propagate to assembler
                throw error;
            }
        }
        return instructions;
    }

private:
    Instruction get_instruction(token token)
    {
        if (token.first != TokenType::IDENTIFIER)
        {
            throw "ERROR : Not an identifier";
        }
        // return corresponding instruction type
        if (token.second == "halt")
            return Instruction::HALT;
        else if (token.second == "nop")
            return Instruction::NOP;
        else if (token.second == "addq")
            return Instruction::ADDQ;
        else if (token.second == "andq")
            return Instruction::ANDQ;
        else if (token.second == "subq")
            return Instruction::SUBQ;
        else if (token.second == "xorq")
            return Instruction::XORQ;
        else
            return Instruction::INCORRECT;
    }
    // pretty big function
    bool check_syntax(Instruction instr, std::vector<token> tokens)
    {
        // basically a bunch of guard clauses, can safely use if cause enums
        // assumes first token has already been verified as a valid identifier
        // still not supporting labels
        if (instr == Instruction::INCORRECT)
        {
            // no way this should be encountered, but just in case
            return false;
        }
        if (instr == Instruction::HALT || instr == Instruction::NOP)
        {
            // zero register instructions
            if (tokens.size() != 1)
                return false;
        }
        if (instr == Instruction::ANDQ ||
            instr == Instruction::ANDQ ||
            instr == Instruction::XORQ ||
            instr == Instruction::SUBQ)
        {
            // must be three tokens (2 reg arguments)
            if (tokens.size() != 3)
                return false;
            // must be register args
            if (tokens[1].first != TokenType::REGISTER || tokens[2].first != TokenType::REGISTER)
                return false;
        }
        // one of the guard clauses entered, and no false returned.
        // mutual exclusivity ensures more than one if cant be entered, pattern works.
        return true;
    }

    std::string translate_to_machine(Instruction instr, std::vector<token> tokens)
    {
        // currently just returns a formatted hex string for my clarity, will later return a proper binary string
        // assumes that the given list of tokens is verified and valid
        // will abstract translation rules elsewhere
        std::string code = "0x ";
        if (instr == Instruction::INCORRECT)
            throw "ERROR : Invalid";
        if (instr == Instruction::HALT)
            code.append("00 FF");
        if (instr == Instruction::NOP)
            code.append("10 FF");
        if (instr == Instruction::ADDQ || instr == Instruction::ANDQ || instr == Instruction::SUBQ || instr == Instruction::XORQ)
        {
            code.append("6");
            if (instr == Instruction::ADDQ)
                code.append("0 ");
            if (instr == Instruction::SUBQ)
                code.append("1 ");
            if (instr == Instruction::ANDQ)
                code.append("2 ");
            if (instr == Instruction::XORQ)
                code.append("3 ");
            try
            {
                // translate registers (already verified that they are valid registers)
                auto rA = get_register_code(tokens[1]);
                auto rB = get_register_code(tokens[2]);
                code.append(rA);
                code.append(rB);
                // no constant word currently
            }
            catch (std::string error)
            {
                throw error;
            }
        }
        return code;
    }
    std::string get_register_code(token reg_token)
    {
        if (reg_token.first != TokenType::REGISTER)
        {
            throw "ERROR : Not a register token";
        }
        // hardcoding here for now, will extract elsewhere later
        // supports 4 registers for now, will hardcode rest later
        auto reg = reg_token.second;
        if (reg == "rax")
            return "0";
        else if (reg == "rcx")
            return "1";
        else if (reg == "rdx")
            return "2";
        else if (reg == "rbx")
            return "3";
        else
            throw "ERROR : Unspecified register";
    }
};
