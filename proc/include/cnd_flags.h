#pragma once

class CndCodes
{
private:
    int of;
    int sf;
    int zf;
    bool cnd;

public:
    CndCodes() : of(0), sf(0), zf(0), cnd(false) {}
    void reinitialize()
    {
        of = 0;
        sf = 0;
        zf = 0;
        cnd = false;
    }
    void setCnd(bool set) { cnd = set; }
    int get_of() { return of; }
    int get_sf() { return sf; }
    int get_zf() { return zf; }
    void toggle_OF() { of == 1 ? of = 0 : of = 1; }
    void toggle_SF() { sf == 1 ? sf = 0 : sf = 1; }
    void toggle_ZF() { zf == 1 ? zf = 0 : zf = 1; }
};