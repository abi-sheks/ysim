#include "../include/parser.h"
#include <stdexcept>

void Parser::print_jump_table()
{
    for (auto &item : jump_table)
    {
        std::cout << item.first << " " << item.second;
    }
    std::cout << std::endl;
}
void Parser::resolve_targets(typed_mi &mcode)
{
    if (mcode.first != Instruction::CALL &&
        mcode.first != Instruction::JMP &&
        mcode.first != Instruction::JLE &&
        mcode.first != Instruction::JL &&
        mcode.first != Instruction::JE &&
        mcode.first != Instruction::JNE &&
        mcode.first != Instruction::JGE &&
        mcode.first != Instruction::JG)
    {
        // not a branch instruction
        return;
    }
    auto mcode_words = split_at_whitespaces(mcode.second);
    // last element is expected to be the label name
    auto label_name = mcode_words[mcode_words.size() - 1];
    auto jump_address_pot = jump_table.find(label_name);
    if (jump_address_pot == jump_table.end())
    {
        throw std::runtime_error("ERROR : Label does not exist");
    }
    auto jump_address = jump_address_pot->second;
    // since we directly know that a call/jmp instruction is encoded as
    // 10 characters for address, space, 0x, space, code:func, space, label_name
    // we can extract string before label_name and append jump address
    auto new_mcode_base = std::string(mcode.second.begin(), mcode.second.begin() + 17);
    auto new_mcode = new_mcode_base.append(jump_address);
    mcode.second = new_mcode;
}
typed_mi Parser::first_parse(std::vector<token> instr_token, std::string &curr_address)
{
    // given a stream of tokens, the first token must be either an identifier or a label
    // parser will look up syntax according to identifier and verify, then translate to machine code.
    // first check_syntax()
    // second translate()
    std::string instructions = "";
    if (instr_token[0].first == TokenType::INVALID || instr_token[0].first == TokenType::REGISTER || instr_token[0].first == TokenType::LITERAL)
    {
        throw std::runtime_error("FAILED : Incorrect instruction encountered");
    }
    if (instr_token[0].first == TokenType::LABEL)
    {
        // there can be no other args (apart from address token)
        if (instr_token.size() != 2)
        {
            throw std::runtime_error("FAILED : Incorrect instruction encountered");
        }
        // logic to add label to symbol table
        // address is unchanged i.e label has same address as next identifier
        jump_table.emplace(instr_token[0].second, zero_extend_hex(instr_token[1].second));
        return std::pair(Instruction::INCORRECT, "Label");
    }
    if (instr_token[0].first == TokenType::IDENTIFIER)
    {
        // perform lookup and verify syntax
        // lookup returns instruction name, and translation occurs according to instruction name
        try
        {
            Instruction gen_instr = get_instruction(instr_token[0]);
            if (gen_instr == Instruction::INCORRECT)
                throw std::runtime_error("ERROR : Invalid instruction");

            if (!check_syntax(gen_instr, instr_token))
            {
                throw std::runtime_error("ERROR : Invalid instruction");
            }
            auto machine_instr = translate_to_machine(gen_instr, instr_token);
            // still current instructions address
            instructions.append(zero_extend_hex(curr_address));
            instructions.append(" ");
            instructions.append(machine_instr);
            // compute next address based on instruction and update next_address for next token
            curr_address = compute_next_address(gen_instr, curr_address);
            return std::pair(gen_instr, instructions);
        }
        catch (std::runtime_error &error)
        {
            // propagate to assembler
            throw error;
        }
    }
    // default, should not encounter
    return std::pair(Instruction::INCORRECT, std::string(""));
}

Instruction Parser::get_instruction(token token)
{
    auto instr_to_enum = get_instr_to_enum();
    if (token.first != TokenType::IDENTIFIER)
    {
        throw std::runtime_error("ERROR : Not an identifier");
    }
    // return corresponding instruction type, imported map from utilities
    if (instr_to_enum.find(token.second) == instr_to_enum.end())
    {
        return Instruction::INCORRECT;
    }
    return instr_to_enum.find(token.second)->second;
}
// pretty big function
bool Parser::check_syntax(Instruction instr, std::vector<token> tokens)
{
    // basically a bunch of guard clauses, can safely use if cause enums
    // assumes first token has already been verified as a valid identifier
    // still not supporting labels
    if (instr == Instruction::INCORRECT)
    {
        // no way this should be encountered, but just in case
        return false;
    }
    // zero register (one address token)
    if (instr == Instruction::HALT ||
        instr == Instruction::NOP ||
        instr == Instruction::RET)
    {
        if (tokens.size() != 2)
            return false;
    }

    // 1 register (one address)
    if (instr == Instruction::PUSHQ ||
        instr == Instruction::POPQ)
    {
        if (tokens.size() != 3)
        {
            return false;
        }
        // must be register
        if (tokens[1].first != TokenType::REGISTER)
        {
            return false;
        }
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
        // must be 4 tokens (2 reg arguments) (one address token)
        if (tokens.size() != 4)
            return false;
        // must be register args
        if (tokens[1].first != TokenType::REGISTER || tokens[2].first != TokenType::REGISTER)
            return false;
    }
    // 1 reg 1 literal
    if (instr == Instruction::IRMOVQ)
    {
        if (tokens.size() != 4)
            return false;
        if (tokens[1].first != TokenType::LITERAL || tokens[2].first != TokenType::REGISTER)
            return false;
    }
    // 2 reg 1 literal
    if (instr == Instruction::MRMOVQ)
    {
        if (tokens.size() != 5)
            return false;
        if (tokens[1].first != TokenType::LITERAL || tokens[2].first != TokenType::REGISTER || tokens[3].first != TokenType::REGISTER)
            return false;
    }
    if (instr == Instruction::RMMOVQ)
    {
        if (tokens.size() != 5)
            return false;
        if (tokens[1].first != TokenType::REGISTER || tokens[2].first != TokenType::LITERAL || tokens[3].first != TokenType::REGISTER)
            return false;
    }
    if (instr == Instruction::CALL ||
        instr == Instruction::JMP ||
        instr == Instruction::JLE ||
        instr == Instruction::JL ||
        instr == Instruction::JE ||
        instr == Instruction::JNE ||
        instr == Instruction::JGE ||
        instr == Instruction::JG)
    {
        if (tokens.size() != 3)
            return false;
        if (tokens[1].first != TokenType::TARGET)
            return false;
    }
    // one of the guard clauses entered, and no false returned.
    // mutual exclusivity ensures more than one if cant be entered, pattern works.
    return true;
}

std::string Parser::translate_to_machine(Instruction instr, std::vector<token> tokens)
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
        throw std::runtime_error("ERROR : Invalid");
    }
    code.append(code_part->second);
    code.append(func_part->second);
    try
    {
        // translate registers (already verified that they are valid registers), but could be NOP or HALT handled inside
        // handle for non 2-reg cases (got greedy for cleanliness and shat on my logic here lol)
        if (instr == Instruction::HALT || instr == Instruction::NOP || instr == Instruction::RET)
        {
        }
        else if (instr == Instruction::IRMOVQ)
        {
            auto rB = get_register_code(tokens[2], instr);
            code.append(" ");
            code.append("F");
            code.append(rB);
            code.append(" ");
            code.append(zero_extend_hex(tokens[1].second));
        }
        else if (instr == Instruction::MRMOVQ)
        {
            auto rB = get_register_code(tokens[2], instr);
            auto rA = get_register_code(tokens[3], instr);
            code.append(" ");
            code.append(rA);
            code.append(rB);
            code.append(" ");
            code.append(zero_extend_hex(tokens[1].second));
        }
        else if (instr == Instruction::RMMOVQ)
        {
            auto rB = get_register_code(tokens[1], instr);
            auto rA = get_register_code(tokens[3], instr);
            code.append(" ");
            code.append(rA);
            code.append(rB);
            code.append(" ");
            code.append(zero_extend_hex(tokens[2].second));
        }
        else if (instr == Instruction::POPQ || instr == Instruction::PUSHQ)
        {
            // dont want to use else as catch all branch, its causing subtle bugs
            // i prefer this explicity even though LOC increases.
            auto rA = get_register_code(tokens[1], instr);
            code.append(" ");
            code.append(rA);
            code.append("F");
        }
        else if (instr == Instruction::CALL ||
                 instr == Instruction::JMP ||
                 instr == Instruction::JLE ||
                 instr == Instruction::JL ||
                 instr == Instruction::JE ||
                 instr == Instruction::JNE ||
                 instr == Instruction::JGE ||
                 instr == Instruction::JG)
        {
            // in first pass, simply append the target as is, and build symbol table, resolve to address on second pass
            code.append(" ");
            code.append(tokens[1].second);
        }
        else
        {
            // opq
            auto rA = get_register_code(tokens[1], instr);
            auto rB = get_register_code(tokens[2], instr);
            code.append(" ");
            code.append(rA);
            code.append(rB);
        }
        // no constant word currently
    }
    catch (std::runtime_error& error)
    {
        throw error;
    }
    return code;
}
std::string Parser::get_register_code(token reg_token, Instruction instr)
{
    if (instr == Instruction::INCORRECT)
        throw std::runtime_error("ERROR : Invalid");
    // get_registers() for reg_ref
    auto registers = get_registers();
    if (reg_token.first != TokenType::REGISTER)
    {
        throw std::runtime_error("ERROR : Not a register token");
    }
    auto reg = reg_token.second;
    if (registers.find(reg) == registers.end())
    {
        throw std::runtime_error("ERROR : Unspecified register");
    }
    else
    {
        return registers.find(reg)->second;
    }
}
std::string Parser::compute_next_address(Instruction instr, std::string current_address)
{
    std::string next_addr;
    // converting string to int
    int addr_in_bytes = 0;
    std::stringstream to_int;
    to_int << current_address;
    to_int >> addr_in_bytes;
    // adding +8 for 1 byte
    auto offsets = get_offsets();
    if (offsets.find(instr) == offsets.end())
    {
        throw std::runtime_error("ERROR : Invalid instruction");
    }
    auto req_offset = offsets.find(instr)->second;
    addr_in_bytes += req_offset;
    std::stringstream to_string;
    to_string << addr_in_bytes;
    to_string >> next_addr;
    return next_addr;
}