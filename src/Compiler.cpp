#include <algorithm>
#include <exception>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Parser.h"
#include "Bytecode.h"
#include "Compiler.h"
#include "Token.h"

using namespace std;
using namespace Bytecode;

// translate a token from the parsed token stream into in bytecode
Bytecode::Instruction* translate(Token& token) {
  Bytecode::Instruction* instruction = new Bytecode::Instruction;

	switch (token.type) {
		case KEYWORD:
			// TODO: clean hardcoded keyword patterns
			if (token.pattern == "print") 
				instruction->operation = Opcode::PRINT;
			else if (token.pattern == "start") 
				instruction->operation = Opcode::NOP;
			else if (token.pattern == "end") 
				instruction->operation = Opcode::NOP;
			break;

		case STRING_LITERAL:
			instruction->operation = Opcode::PUSH;
			instruction->operand = token;
			break;
		case INTEGER_LITERAL:
			instruction->operation = Opcode::PUSH;
			instruction->operand = token;
			break;

		case ARITHMETIC_OPERATOR:
			if (token.pattern == "+")
				instruction->operation = Opcode::ADD;
			else if (token.pattern == "-")
				instruction->operation = Opcode::SUB;
			else if (token.pattern == "*")
				instruction->operation = Opcode::MUL;
			else if (token.pattern == "/")
				instruction->operation = Opcode::DIV;
			break;

		default:
			instruction->operation = Opcode::NOP;
	}

    return instruction;
}

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* compile(string& sourceCode) 
{
	cout << "\n======== Generating Tokens ========\n" << endl;
    vector<Token> tokens = lex(sourceCode);

	cout << "\n======== Parsing Expressions ========\n" << endl;
	vector<Token>* stream = parser(&tokens);

	cout << "\n======== Token Stream ========\n";
    for (Token token : *stream) 
	{
        cout << token.pattern << " ";
    }
    cout << "\n\n";

    vector<Bytecode::Instruction>* bytecode = new vector<Bytecode::Instruction>;
	for (Token token : *stream) {
	  Bytecode::Instruction* instruction = translate(token);
	  bytecode->push_back(*instruction);
	  stream->pop_back();
	}

    return bytecode;
}
