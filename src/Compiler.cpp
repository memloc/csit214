#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Parser.h"
#include "Bytecode.h"
#include "Compiler.h"

using namespace std;


// translate tokens from the token stream into instructions in bytecode representation
Bytecode::Instruction translate(vector<Token>& statementStream) {
    Bytecode::Instruction instruction;

    // create an instruction from one or more tokens

    return instruction;
}

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* compile(string& sourceCode) {
	cout << "\n======== Generating Tokens ========\n" << endl;
    vector<Token> tokens = lex(sourceCode);

	cout << "\n======== Parsing Expressions ========\n" << endl;
	vector<Token>* stream = parser(&tokens);

	cout << "\n======== Token Stream ========\n";
    for (Token token : *stream) {
        cout << token.pattern << " ";
    }
    cout << "\n\n";

    vector<Bytecode::Instruction>* bytecode; 
    return bytecode;
}
