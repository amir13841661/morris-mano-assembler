#include <string.h>

u_int16_t memoryReferenceInstructions(char *instruction)
{
    if (strcmp(instruction, "AND") == 0)
    {
        return 0;
    }
    else if (strcmp(instruction, "ADD") == 0)
    {
        return 0b0001000000000000;
    }
    else if (strcmp(instruction, "LDA") == 0)
    {
        return 0b0010000000000000;
    }
    else if (strcmp(instruction, "STA") == 0)
    {
        return 0b0011000000000000;
    }
    else if (strcmp(instruction, "BUN") == 0)
    {
        return 0b0100000000000000;
    }
    else if (strcmp(instruction, "BSA") == 0)
    {
        return 0b0101000000000000;
    }
    else if (strcmp(instruction, "ISZ") == 0)
    {
        return 0b0110000000000000;
    }
    return 1;
}

u_int16_t nonmemoryReferenceInstructions(char *instruction)
{
    if (strcmp(instruction, "HLT") == 0)
    {
        return 0b0111000000000001;
    }
    else if (strcmp(instruction, "SZE") == 0)
    {
        return 0b0111000000000010;
    }
    else if (strcmp(instruction, "SZA") == 0)
    {
        return 0b0111000000000100;
    }
    else if (strcmp(instruction, "SNA") == 0)
    {
        return 0b0111000000001000;
    }
    else if (strcmp(instruction, "SPA") == 0)
    {
        return 0b0111000000010000;
    }
    else if (strcmp(instruction, "INC") == 0)
    {
        return 0b0111000000100000;
    }
    else if (strcmp(instruction, "CIL") == 0)
    {
        return 0b0111000001000000;
    }
    else if (strcmp(instruction, "CIR") == 0)
    {
        return 0b0111000010000000;
    }
    else if (strcmp(instruction, "CME") == 0)
    {
        return 0b0111000100000000;
    }
    else if (strcmp(instruction, "CMA") == 0)
    {
        return 0b0111001000000000;
    }
    else if (strcmp(instruction, "CLE") == 0)
    {
        return 0b0111010000000000;
    }
    else if (strcmp(instruction, "CLA") == 0)
    {
        return 0b0111100000000000;
    }
    else if (strcmp(instruction, "INP") == 0)
    {
        return 0b1111100000000000;
    }
    else if (strcmp(instruction, "OUT") == 0)
    {
        return 0b1111010000000000;
    }
    else if (strcmp(instruction, "SKI") == 0)
    {
        return 0b1111001000000000;
    }
    else if (strcmp(instruction, "SKO") == 0)
    {
        return 0b1111000100000000;
    }
    else if (strcmp(instruction, "ION") == 0)
    {
        return 0b1111000010000000;
    }
    else if (strcmp(instruction, "IOF") == 0)
    {
        return 0b1111000001000000;
    }
    return 1;
}
