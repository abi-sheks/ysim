#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <bitset>

std::string address_to_binary(unsigned long value)
{
    // can handle all 64 bit values
    std::string s = std::bitset<64>(value).to_string();
    std::cout << s << '\n';
    return s;
}

// to extract tag, set, and block offset bits
std::vector<std::string> get_bit_info(std::string bin_addr, int o1, int o2)
{
    std::vector<std::string> bits;
    auto tag_bits = bin_addr.substr(0, o1);
    auto set_index_bits = bin_addr.substr(o1, o2 - o1);
    auto block_offset_bits = bin_addr.substr(o2, bin_addr.length() - o2);
    bits.push_back(tag_bits);
    bits.push_back(set_index_bits);
    bits.push_back(block_offset_bits);
    return bits;
}

int bitstring_to_int(std::string bits)
{
    // assuming unsigned
    int accum = 0;
    for (int i = 0; i < bits.length(); i++)
    {
        accum += static_cast<int>(pow(2, bits.length() - 1 - i));
    }
    return accum;
}