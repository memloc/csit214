#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <iostream>

#include "Token.h"
#include "Bytecode.h"

using namespace std;


// translate tokens from the token stream into instructions in bytecode
vector<Bytecode::Instruction> translate(vector<Token>&);

// performs the entire process of lexing, parsing and translation from source code into the bytecode
vector<Bytecode::Instruction>* compile(string &);

#endif // COMPILER_H
