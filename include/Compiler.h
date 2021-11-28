#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <iostream>

#include "Token.h"
#include "Bytecode.h"

namespace Compiler {

    using namespace std;

    enum ExceptionType {
        NONE,
        UNDEFINED_BEHAVIOR,
    };

    struct Exception {
        ExceptionType type;
        string message;
    };

    // produces a token from input source code
    Parser::Token lex(string&);

    // produce the token stream
    vector<Parser::Token>* parse(string&);

    // translate tokens from the token stream into instructions in bytecode representation
    Bytecode::Instruction translate(vector<Parser::Token>&);

    // performs lexing, parsing, and translation into the bytecode representation of the program
    vector<Bytecode::Instruction>* compile(string &);

}

#endif // COMPILER_H