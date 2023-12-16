#pragma once
#include "instruction.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include "token.h"

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
        auto instr_to_enum = get_instr_to_enum();
        if (token.first != TokenType::IDENTIFIER)
        {
            throw "ERROR : Not an identifier";
        }
        // return corresponding instruction type, imported map from utilities
        if (instr_to_enum.find(token.second) == instr_to_enum.end())
        {
            return Instruction::INCORRECT;
        }
        return instr_to_enum.find(token.second)->second;
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
        // zero register
        if (instr == Instruction::HALT ||
            instr == Instruction::NOP)
        {
            // zero register instructions
            if (tokens.size() != 1)
                return false;
        }

        // 2 register
        if (instr == Instruction::ANDQ ||
            instr == Instruction::ANDQ ||
            instr == Instruction::XORQ ||
            instr == Instruction::SUBQ ||
            instr == Instruction::RRMOVQ ||
            instr == Instruction::CMOVLE ||
            instr == Instruction::CMOVL ||
            instr == Instruction::CMOVE ||
            instr == Instruction::CMOVNE ||
            instr == Instruction::CMOVGE ||
            instr == Instruction::CMOVG)
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
        auto codes = get_codes();
        auto function_specs = get_function_specs();
        // currently just returns a formatted hex string for my clarity, will later return a proper binary string
        // assumes that the given list of tokens is verified and valid
        // will abstract translation rules elsewhere
        std::string code = "0x ";
        auto code_part = codes.find(instr);
        auto func_part = function_specs.find(instr);
        if (code_part == codes.end() || func_part == function_specs.end())
        {
            throw "ERROR : Invalid";
        }
        code.append(code_part->second);
        code.append(func_part->second);
        try
        {
            // translate registers (already verified that they are valid registers), but could be NOP or HALT handled inside
            // handle for non 2-reg cases (got greedy for cleanliness and shat on my logic here lol)
            if (instr == Instruction::HALT || Instruction::NOP)
            {
                code.append("FF");
            }
            else
            {
                auto rA = get_register_code(tokens[1], instr);
                auto rB = get_register_code(tokens[2], instr);
                code.append(rA);
                code.append(rB);
            }
            // no constant word currently
        }
        catch (std::string error)
        {
            throw error;
        }
        return code;
    }
    std::string get_register_code(token reg_token, Instruction instr)
    {
        if (instr == Instruction::INCORRECT)
            throw "ERROR : Invalid";
        // get_registers() for reg_ref
        auto registers = get_registers();
        if (reg_token.first != TokenType::REGISTER)
        {
            throw "ERROR : Not a register token";
        }
        auto reg = reg_token.second;
        if (registers.find(reg) == registers.end())
        {
            throw "ERROR : Unspecified register";
        }
        else
        {
            return registers.find(reg)->second;
        }
    }
};
