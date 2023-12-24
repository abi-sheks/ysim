#pragma once
#include <map>
#include <string>
#include <cmath>
#include <vector>

// interface
// 1 byte words stored
// assuming binary strings are stored in memory.
class Cache
{
public:
    virtual ~Cache() = default;
    virtual char read(char *address) = 0;
    virtual std::string on_read_miss(char *address, int block_offset) = 0;
    virtual void write(char *address, char value) = 0;
    virtual std::string on_write_miss(char *address, char value, int block_offset) = 0;
};

class CacheLine
{
public:
    int B;
    int dirty_bit;
    int valid_bit;
    char *block;
    std::string tag_bits;
    CacheLine(int s);
    CacheLine(int s, char *arr);
    ~CacheLine()
    {
        delete[] block;
    }
};
class Set
{
public:
    int B, E;
    std::vector<CacheLine> lines;
    Set(int s, int e);
};

// Write back, write allocate.
class DirectMappedCache : public Cache
{
private:
    // the underlying main memory is stored as a simple set of key value pairs,
    //  where the key is the address and value is the word
    std::map<char *, char> main_memory;
    int s, e, b;
    int S, E, B;
    std::vector<Set> sets;

public:
    DirectMappedCache(int _s);
    char read(char *address) override;
    void write(char *address, char value) override;
    // read and write miss can be handled in the same way as it is write allocate.
    // no need to implement on_write_miss;
    std::string on_read_miss(char *address, int block_offset) override;
    std::string on_write_miss(char *address, char value, int block_offset) override;

private:
    void write_back(std::string tag_bits, std::string set_bits, char*old_block);
};
