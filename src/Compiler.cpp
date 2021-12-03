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

// converts a token into one or more words
vector<Word> convert(Token& token) {
  vector<Word> statement;
  return statement;
};

// Translate all of the tokens in the token stream into bytecode
vector<Bytecode::Instruction> translate(vector<Token>& tokenStream) {
  vector<Bytecode::Instruction> bytecode;
  Bytecode::Instruction* instruction = new Bytecode::Instruction;

  for (Token token : tokenStream) {
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
			//
			//
			//
			//
			//
			


			break;
		case INTEGER_LITERAL:
			instruction->operation = Opcode::PUSH;
			//
			// instruction->operand
			//
			//
			

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
  }

  return bytecode;
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
	//
	// Translate bytecode 
	//
	//
	//
		 

    return bytecode;
}
