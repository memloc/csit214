#include <algorithm>
#include <cstddef>
#include <exception>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Parser.h"
#include "Bytecode.h"
#include "Compiler.h"
#include "Token.h"
#include "Lexer.h"

using namespace std;
using namespace Bytecode;

// Convert the pattern contained within a token into a WORD, and pair it with an operation to form a set of instructions
vector<Bytecode::Instruction>* convert(Token &token)
{
	vector<Bytecode::Instruction>* data = new vector<Bytecode::Instruction>;

	// A Word only has 32-bits allocated to data storage, so it can only store 4 characters 
	size_t totalChars = token.pattern.size();
	size_t numWords = (totalChars % 4 == 0) ? (totalChars/4) : (totalChars/4) + 1;

	// 
	size_t curChar = 0;
	for (size_t curWord = numWords; curWord > 0; curWord--) {
		Instruction inst;
		inst.operation = Opcode::PUSH;
		inst.operand.type = WordType::CHAR32_T;

		// Initialize each character of the instruction, set it to null terminator if it is outside of the string
		inst.operand.memory.asChar32.c0 = (curChar == totalChars) ? '\0' : token.pattern.at(curChar++);
		inst.operand.memory.asChar32.c1 = (curChar == totalChars) ? '\0' : token.pattern.at(curChar++);
		inst.operand.memory.asChar32.c2 = (curChar == totalChars) ? '\0' : token.pattern.at(curChar++);
		inst.operand.memory.asChar32.c3 = (curChar == totalChars) ? '\0' : token.pattern.at(curChar++);

		data->push_back(inst);
	}

	// Because the VM will read the string in chunks of 4 characters, we have to reverse the stream 
	reverse(data->begin(), data->end());
	return data;
};

// Translate all of the tokens in the token stream into bytecode
vector<Bytecode::Instruction>* translate(vector<Token> &tokenStream)
{
    vector<Bytecode::Instruction>* bytecode = new vector<Bytecode::Instruction>;

	for (Token token : tokenStream)
	{
		switch (token.type)
		{
		case KEYWORD: {

			// TODO: clean hardcoded keyword patterns
			if (token.pattern == "print")
			{
				Instruction inst1 { .operation = Bytecode::Opcode::PEEK };
				Instruction inst2 { .operation = Bytecode::Opcode::PRINT };
				Instruction inst3 { .operation = Bytecode::Opcode::POP };
				bytecode->push_back(inst1);
				bytecode->push_back(inst2);
				bytecode->push_back(inst3);
			}
			else if (token.pattern == "start")
			{
				// unimplemented
			}
			else if (token.pattern == "end")
			{
				// unimplemented
			}
			break;
		}

		case STRING_LITERAL: {
		    vector<Instruction>* instructions = convert(token);
			for (Instruction set: *instructions) {
				bytecode->push_back(set);
			}
		} 
		break;

		case INTEGER_LITERAL: {
			Instruction inst;
			inst.operation = Bytecode::Opcode::PUSH;
			inst.operand.type = Bytecode::WordType::INT32_T;
			inst.operand.memory.asInt32 = stoi(token.pattern);
			bytecode->push_back(inst);
		}
		break;

		case ARITHMETIC_OPERATOR:
			if (token.pattern == "+") 
			{
				Instruction inst { .operation = Opcode::ADD };
				bytecode->push_back(inst);
			}
			else if (token.pattern == "-") 
			{
				Instruction inst { .operation = Opcode::ADD };
				bytecode->push_back(inst);
			}
			else if (token.pattern == "*")
			{
				Instruction inst { .operation = Opcode::ADD };
				bytecode->push_back(inst);
			}
			else if (token.pattern == "/") 
			{
				Instruction inst { .operation = Opcode::ADD };
				bytecode->push_back(inst);
			}
			break;
		}
	}

	return bytecode;
}

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* compile(string &sourceCode) {
  cout << "\n======== Generating Tokens ========\n" << endl;
  vector<Token> tokens = lex(sourceCode);

  cout << "\n======== Parsing Expressions ========\n" << endl;
  vector<Token> *stream = parser(&tokens);

  cout << "\n======== Token Stream ========\n";
  for (Token token : *stream) {
    cout << token.pattern << " ";
  }
  cout << "\n\n";

  vector<Bytecode::Instruction>* bytecode = translate(*stream);

  return bytecode;
}
