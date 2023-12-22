//some assumptions about the memory system implemented here

//Main Memory

//Though im designing main memory in a cache like way, it will be able store all possible addresses due to the 
//following assumptions 

//I will simplify our assumptions such that a block ends up storing a word of information.

//Word size = 1 byte = 8 bits (m = 1)
//The "main memory" is represented as a fully associative cache with block size of 1 byte, (1 byte per block),
//and a capacity of 1024 bytes. (128 cache lines in the set).

//this is assuming an address is 8 bits (word size = address size) long, resulting in (t = 1 - (0 + 0) =)1 tag bit, 1 valid bit, and the 8 bits/
//2 bytes/ word stored in the block.
//to represent every possible address with a word size of 1 byte, we need to be able to store 2^8 = 256 values. so we need a capacity of (no of lines).
//now, as we wish to store 256 different words or (in this case) bytes, we need Capacity = 256 = no of lines, as each line holds a byte.
//so final parameters, enabling us to emulate "main memory"

//assuming word size = 1 byte
//Fully associative, 256 lines in set, block size of 1 byte. Allows us to store all 1 byte values. can be extended for larger word sizes.
class MainMemory
{

};