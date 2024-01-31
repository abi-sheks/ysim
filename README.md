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
# Cache  
The ```mem``` directory contains an implementation of a directly mapped, write-back write-allocate cache. It assumes a variable set size, but assumes a fixed block size of 8 bytes, where each word is 1 byte (i.e the block is implemented as an array of chars).  
It assumes a address size of 64 bits, and represents the lower memoy level as a map, where the keys are addresses (char pointers) and the values are bytes (chars).  
# Processor 
The ```proc``` directory contains a five stage sequential processor simulation. The processor has some not-so-airtight error handling in some sections, mostly aborts with an error.what().  
It supports the full Y86-64 instruction set, and provides ```exmem``` and ```exreg``` functions to examine memory and register state respectively after program execution.  
The registers and memory are zero initialized at the start.  
The processor expects 16 character long strings (representing 8 byte word) to operate correctly. Not writing your assembly with proper 8 byte/16 character addresses/constants could result in unexpected behaviour.  
The addressing display/calculations are all kept in decimal so that I could have a better DevEx. At some point in the future, I will go through the tedium of converting to and from hex in between operations and storage.  
There is no cache integration. This is a standalone implementation completely separate from my cache implementation. I hope to integrate the two in the future.

## Usage
CMake is being used to build the project. 
Currently, I've added no sort of public API to work with the cache, as its supposed to act as the memory unit for the planned processor.  
The main file runs the assembler and processor, so after building the project, you can use ```./ysim <asm-file>``` to see the assembled output in the command line.  
The assembler assembles the ALP in ```<asm-file>``` and passes them to the processor, which executes them sequentially. an exreg is run after processing so you can see the effect of the program execution on program state. You can accordingly assemble, execute and examine registers and memory using the same functions you see in ```main.cpp```, or you can view the public API in the ```/include```s.
