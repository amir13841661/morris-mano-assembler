#include <string.h>

u_int16_t memoryReferenceInstructions(char *instruction)
{
    if (instruction == "AND")
    {
        return 0;
    }
    else if (instruction == "ADD")
    {
        return 0b0001000000000000;
    }
    else if (instruction == "LDA")
    {
        return 0b0010000000000000;
    }
    else if (instruction == "STA")
    {
        return 0b0011000000000000;
    }
    else if (instruction == "BUN")
    {
        return 0b0100000000000000;
    }
    else if (instruction == "BSA")
    {
        return 0b0101000000000000;
    }
    else if (instruction == "ISZ")
    {
        return 0b0110000000000000;
    }
}

u_int16_t nonmemoryReferenceInstructions(char *instruction)
{
    if (instruction == "HLT")
    {
        return 0b0111000000000000;
    }
    else if (instruction == "SZE")
    {
        return 0b0111000000000001;
    }
    else if (instruction == "SZA")
    {
        return 0b0111000000000010;
    }
    else if (instruction == "SNA")
    {
        return 0b0111000000000011;
    }
    else if (instruction == "SPA")
    {
        return 0b0111000000000100;
    }
    else if (instruction == "INC")
    {
        return 0b0111000000000101;
    }
    else if (instruction == "CIL")
    {
        return 0b0111000000000110;
    }
    else if (instruction == "CIR")
    {
        return 0b0111000000000111;
    }
    else if (instruction == "CME")
    {
        return 0b0111000000001000;
    }
    else if (instruction == "CMA")
    {
        return 0b0111000000001001;
    }
    else if (instruction == "CLE")
    {
        return 0b0111000000001010;
    }
    else if (instruction == "CLA")
    {
        return 0b0111000000001011;
    }
    else if (instruction == "INP")
    {
        return 0b1111000000001011;
    }
    else if (instruction == "OUT")
    {
        return 0b1111000000001010;
    }
    else if (instruction == "SKI")
    {
        return 0b1111000000001001;
    }
    else if (instruction == "SKO")
    {
        return 0b1111000000001000;
    }
    else if (instruction == "ION")
    {
        return 0b1111000000000111;
    }
    else if (instruction == "IOF")
    {
        return 0b1111000000000110;
    }
}
