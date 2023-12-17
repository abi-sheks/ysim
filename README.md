# Purpose
This is an educational project i've taken up to ramify my learnings in computer architecture from [_Computer Systems : A Programmer's Perspective_](//https://csapp.cs.cmu.edu/). The project will center around Y86-64, a subset of x86-64 (with more RISC-like features like load/store) as detailed in the book itself. I chose this ISA because of some design choices like condition codes that I like, and some RISC ideas like load/store that I also prefer. 
# Plans
I aim to write an assembler for the ISA in C++, and an implementation of a simple pipelined processor as detailed in the text. Preferably, I would implement the processor in a HDL like Verilog, though a C++ implementation could also manifest due to a lack of time.  
Currently, an assembler has been developed, I will start on the processor after.  
# Assembler
You can use the file ```test.s``` or any other assembly file in Y86-64 to test out the assembler.  
The addressing starts from 0x000 and absolute addresses are being used for branch instructions (as specified). The addressing modes used are the ones Y86 supports, register-register, and base+displacement for memory.  
Will add support for directives soon once i figure out the specification for that.  
Incorrect assembly will cause immediate program termination.  
## Usage
CMake is being used to build the project. You can build it quite easily by just using ```g++``` and linking the ```assembler.h``` header file.  
Ex:- Say the executable you've built is called ```yassembler```, ```./yassembler ./test.s``` will print out the machine encoding in hex in the terminal (for ***Linux*** systems).
