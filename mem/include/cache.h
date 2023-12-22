#pragma once
#include <string>
#include <cmath>
#include <vector>

// interface
// assuming binary strings are stored in memory.
// mixins would be so great here lol.
class Cache
{
public:
    virtual ~Cache() = default;
    virtual int read(long address) = 0;
    virtual int on_read_miss(long address) = 0;
    virtual void write(long address, int value) = 0;
    virtual void on_write_miss(long address, int value) = 0;
};

class CacheLine
{
public:
    int B;
    int dirty_bit;
    int valid_bit;
    char *block;
    std::string tag_bits;
    CacheLine(int s, int b);
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
    Set(int s, int b, int e);
};

class DirectMappedCache : public Cache
{
private:
    int s, e, b;
    int S, E, B;
    std::vector<Set> sets;

public:
    DirectMappedCache(int _s, int _b);
    int read(long address) override;
};
