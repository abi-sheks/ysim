#include "../include/cache.h"
#include "../include/utilities.h"
#include <stdexcept>

CacheLine::CacheLine(int s)
{
    dirty_bit = 0;
    valid_bit = 0;
    // signifies empty cache
    tag_bits = "n";
        B = 8;
        block = new char[8];
    for (int i = 0; i < B; i++)
    {
        block[i] = 'n';
    }
}
CacheLine::CacheLine(int s, char *arr)
{
    dirty_bit = 0;
    valid_bit = 0;
    // signifies empty cache
    tag_bits = "n";
        B = 8;
        block = new char[8];
    // deep copy
    for (int i = 0; i < B; i++)
    {
        block[i] = arr[i];
    }
}

Set::Set(int s, int e)
{
    E = e;
    for (int i = 0; i < e; i++)
    {
        auto line = CacheLine(s);
        lines.push_back(line);
    }
}

DirectMappedCache::DirectMappedCache(int _s)
{
    s = _s;
    b = 3;
    S = static_cast<int>(pow(2, s));
    B = static_cast<int>(pow(2, b));
    E = 1;
    e = 0;
    for (int i = 0; i < s; i++)
    {
        auto set = Set(s, E);
        sets.push_back(set);
    }
}
char DirectMappedCache::read(char *address)
{
    // assuming 64 bit address size
    int t = 64 - (s + b);
    auto address_bin = address_to_binary((unsigned long)address);
    std::vector<std::string> bit_info = get_bit_info(address_bin, t, s);
    auto set_no = bitstring_to_int(bit_info[1]);
    if (set_no > sets.size())
    {
        std::runtime_error("Error! set_no is greater than max size");
    }
    // direct mapped, so we directly access the only line
    auto required_set = sets[set_no];
    auto line = required_set.lines[0];
    auto block_offset = bitstring_to_int(bit_info[2]);
    if (line.valid_bit == 0 || bit_info[0] != line.tag_bits)
    {
        // miss
        // check for write-back before evicting the line
        if (line.dirty_bit == 1)
        {
            write_back(line.tag_bits, bit_info[1], line.block);
            line.dirty_bit = 0;
        }
        auto new_line = on_read_miss(address, block_offset);
        // replace the line by deep copy
        for (int i = 0; i < line.B; i++)
        {
            line.block[i] = new_line[i];
        }
        line.tag_bits = bit_info[0];
        line.valid_bit = 1;
    }
    // return specific value, line replaced on miss
    char val = line.block[block_offset];
    return val;
}
void DirectMappedCache::write(char *address, char value)
{
    // assuming 64 bit address size
    int t = 64 - (s + b);
    auto address_bin = address_to_binary((unsigned long)address);
    std::vector<std::string> bit_info = get_bit_info(address_bin, t, s);
    auto set_no = bitstring_to_int(bit_info[1]);
    if (set_no > sets.size())
    {
        throw std::runtime_error("Error! set_no is greater than max size");
    }
    auto required_set = sets[set_no];
    // direct mapped, so we directly access the only line
    auto line = required_set.lines[0];
    auto block_offset = bitstring_to_int(bit_info[2]);
    if (line.valid_bit == 0 || bit_info[0] != line.tag_bits)
    {
        // miss
        // as it is write allocate, just pull the lower line and update in the cache itself
        // check for write-back before evicting the line.
        if (line.dirty_bit == 1)
        {
            // giving old lines tag bits and set bits
            write_back(line.tag_bits, bit_info[1], line.block);
            line.dirty_bit = 0;
        }
        std::string new_line = on_read_miss(address, block_offset);
        // deep copy
        for (int i = 0; i < line.B; i++)
        {
            line.block[i] = new_line[i];
        }
        // change tag bits
        line.tag_bits = bit_info[0];
        line.valid_bit = 1;
    }
    // update the specific value.
    line.dirty_bit = 1;
    line.block[block_offset] = value;
}

std::string DirectMappedCache::on_read_miss(char *address, int block_offset)
{
    auto valueptr = main_memory.find(address);
    if (valueptr == main_memory.end())
    {
        throw std::runtime_error("Error: Such a value does not exist");
    }
    char value = valueptr->second;
    // populate cache. detect set no and replace the only line with a line from main memory.
    // fetch entire corresponding line from memory, based on where the required value was in the block
    auto base_address = address - block_offset;
    auto final_address = base_address + 7;
    std::string result = "";
    for (char *i = base_address; i < final_address; i++)
    {
        auto accum = main_memory.find(i);
        if (accum == main_memory.end())
        {
            throw std::runtime_error("ERROR : item not found");
        }
        result += accum->second;
    }
    return result;
}

std::string DirectMappedCache::on_write_miss(char *address, char value, int block_offset)
{
    // no need to implement
}

void DirectMappedCache::write_back(std::string tag_bits, std::string set_bits, char *old_block)
{
    auto base = old_block;
    for (int i = 0; i < 8; i++)
    {
        main_memory[base + i] = old_block[i];
    }
}