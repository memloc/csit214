#ifndef BYTECODE_H
#define BYTECODE_H

#include <iostream>

#include "Token.h"

namespace Bytecode {

    enum class Opcode:int8_t {
        PUSH,
        POP,
    };

    struct Operand {
        Parser::Token token;
    };

    // A pairing of an operation and operand
    struct Instruction {
        Opcode operation;
        Operand param;
    };

}

#endif // BYTECODE_H