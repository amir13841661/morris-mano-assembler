# 🖥️ Morris Mano 16-Bit Assembler

## Description
This project is an assembler based on the Morris Mano book's "Basic Computer" (Chapter 5 & 6). I did my best to obey the rules in the book and write the assembler based off of them to ensure a faithful recreation of the 16-bit instruction set.



## Features
- **Custom File Input**: Read your own assembly source files (.asm or .txt) and transform them into valid machine code.
- **Hexadecimal Output**: Generates an output file formatted in hexadecimal, ready for a simulator or memory load.
- **Error Handling**: Built-in validation to stop common mistakes like invalid opcodes, undefined labels, or memory overlaps.
- **Two-Pass Logic**: Correct handles forward-referencing labels by scanning the file twice—once for symbols and once for code generation.




## 🏗️ Technical Specification

### Instruction Format
The assembler maps every instruction to a 16-bit word according to the Mano ISA:
- **Bit 15**: Indirect Addressing bit ($I$).
- **Bits 12–14**: Opcode ($000$ through $111$).
- **Bits 0–11**: Address or Register/IO operation code.

### Supported Instruction Set
| Type | Instructions | Hex Range |
| :--- | :--- | :--- |
| **MRI** | AND, ADD, LDA, STA, BUN, BSA, ISZ | 0xxx - 6xxx (Direct) / 8xxx - Exxx (Indirect) |
| **Register-Ref** | CLA, CLE, CMA, CME, CIR, CIL, INC, SPA, SNA, SZA, SZE, HLT | 7800 - 7001 |
| **I/O** | INP, OUT, SKI, SKO, ION, IOF | F800 - F040 |

## 🛠️ Quick Install
Run this command to compile and install the assembler globally on your Linux system:
```bash
curl -sSL https://raw.githubusercontent.com/amir13841661/morris-mano-assembler/refs/heads/main/install.sh | bash
```
## manual installation
you could clone the repository and compile main.c using 
```bash
gcc main.c
```
note that you'll have to add it to your bin folder manually in order to use it from anywhere within the system
