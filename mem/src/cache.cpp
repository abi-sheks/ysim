#include "../include/cache.h"
#include "../include/utilities.h"

CacheLine::CacheLine(int s, int b)
{
    dirty_bit = 0;
    valid_bit = 0;
    //signifies empty cache
    tag_bits = "n";
    if (b > 0 && b < 1024)
    {
        B = b;
        block = new char[b];
    }
    else
    {
        B = 8;
        block = new char[8];
    }
}

Set::Set(int s, int b, int e)
{
    E = e;
    for (int i = 0; i < e; i++)
    {
        auto line = CacheLine(s, b);
        lines.push_back(line);
    }
}

DirectMappedCache::DirectMappedCache(int _s, int _b)
{
    s = _s;
    b = _b;
    S = static_cast<int>(pow(2, s));
    B = static_cast<int>(pow(2, b));
    E = 1;
    e = 0;
    for(int i = 0; i < s; i++)
    {
        auto set = Set(s, B, E);
        sets.push_back(set);
    }
}
int DirectMappedCache::read(long address) {
    auto address_bin = address_to_binary(address);
    //assuming 64 bit address size
    int t = 64 - (s + b);
    std::vector<std::string> bit_info = get_bit_info(address_bin, t, s);
    auto set_no = bitstring_to_int(bit_info[1]);
    if(set_no  > sets.size())
    {
        std::cout << "Error! set_no is greater than max size";
        return 0;
    }
    auto required_set = sets[set_no];
    //direct mapped, so we directly access the only line
    auto line = required_set.lines[0];
    if(line.valid_bit == 0 || bit_info[0] != line.tag_bits)
    {
        on_read_miss(address);
    }
    auto block_offset = bitstring_to_int(bit_info[0]);
    int val = 0;
    for(size_t i = block_offset; i < line.B; i++)
    {
        val += line.block[i];
    }
    return val;
}