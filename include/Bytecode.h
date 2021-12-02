#ifndef BYTECODE_H
#define BYTECODE_H

#include <iostream>

#include "Token.h"

namespace Bytecode 
{

    enum class Opcode:int8_t 
    {
        NOP,
        PUSH,
        POP,
        PEEK,
        ADD,
        SUB,
        DIV,
        MUL,
        PRINT,
    };


    // A pairing of an operation and operand
    struct Instruction 
    {
	  Opcode operation;
	  Token operand;
    };

}

#endif // BYTECODE_H
