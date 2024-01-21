#pragma once
#include <vector>
#include "../../global/utils.h"
#include "reg.h"
#include <fstream>
#include <sstream>

class RegisterFile
{
private:
    register_reference register_ref;
    Register**registers; 

public:
    RegisterFile();
};