#include <algorithm>
#include <cstddef>
#include <exception>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "../include/Parser.h"
#include "../include/Bytecode.h"
#include "../include/Compiler.h"
#include "../include/Token.h"
#include "../include/Lexer.h"

// Global Iota
int IOTA = 0;

using namespace std;
using namespace Bytecode;

// Convert the pattern contained within a token into a WORD, and pair it with an operation to form a set of instructions
vector<Bytecode::Instruction>* convert(Token &token)
{
	vector<Bytecode::Instruction>* data = new vector<Bytecode::Instruction>;

	// A Word only has 32-bits allocated to data storage, so it can only store 4 characters 
	size_t totalChars = token.pattern.size();
	size_t NUM_CHAR_BYTES = 4;
	size_t numWords = totalChars / NUM_CHAR_BYTES;
	numWords += 2;

	const size_t LAST_WORD = 1; 
	size_t curChar = 0;
	for (size_t curWord = numWords; curWord > LAST_WORD; --curWord) {
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

// Iterator, resets on true
int iota(bool reset=false) 
{
	int n = IOTA++;
	if (reset)
		IOTA = 1;
	return n;
}

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
				// print n-elements
			  Instruction inst;
			  inst.operation = Bytecode::Opcode::PRINT;
			  inst.operand.type = Bytecode::WordType::INT32_T;
			  inst.operand.memory.asInt32 = iota(true);
			  bytecode->push_back(inst);
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
		break;

		case STRING_LITERAL: {
		    vector<Instruction>* instructions = convert(token);
			for (Instruction set: *instructions) {
			  	iota();
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
				Instruction inst { .operation = Opcode::ADD};
				bytecode->push_back(inst);
			}
			else if (token.pattern == "-") 
			{
				Instruction inst { .operation = Opcode::SUB};
				bytecode->push_back(inst);
			}
			else if (token.pattern == "*")
			{
				Instruction inst { .operation = Opcode::MUL};
				bytecode->push_back(inst);
			}
			else if (token.pattern == "/") 
			{
				Instruction inst { .operation = Opcode::DIV};
				bytecode->push_back(inst);
			}
			break;
		}
	}

	reverse(bytecode->begin(), bytecode->end());
	return bytecode;
}

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* compile(string &sourceCode) {
  cout << "===== Tokenizing Input =====" << endl;
  vector<Token> tokens = lex(sourceCode);

  cout << "===== Parsing Expressions =====" << endl;
  vector<Token> *stream = parser(&tokens);

  vector<Bytecode::Instruction>* bytecode = translate(*stream);

  return bytecode;
}
