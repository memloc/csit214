#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <iostream>

#include "Token.h"
#include "Bytecode.h"

namespace Compiler
{

    using namespace std;

    enum ExceptionType
    {
        NONE,
        UNDEFINED_BEHAVIOR,
    };

    struct Exception
    {
        ExceptionType type;
        string message;
    };

    // produces a token from input source code
    vector<Parser::Token> lex(string &);

    // translate tokens from the token stream into instructions in bytecode
    Bytecode::Instruction translate(vector<Parser::Token> &);

    // performs the entire process of lexing, parsing and translation from source code into the bytecode
    vector<Bytecode::Instruction> *compile(string &);

}

#endif // COMPILER_H