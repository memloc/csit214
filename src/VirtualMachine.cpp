#include "Bytecode.h"
#include "Compiler.h"
#include "Token.h"
#include "VirtualMachine.h"
#include <algorithm>

using namespace VM;


  
// execute until finished 
void VirtualMachine::run() {
  while (!bytecode->empty()) {
	step();
  }
}

void VirtualMachine::step(){
  // Execute the next instruction and increment the counter
  counter++;
};

void VirtualMachine::load(Bytecode::Instruction instruction) {
  switch (instruction.operation) {
  case Bytecode::Opcode::NOP:
	break;
  case Bytecode::Opcode::PUSH:
	// Before push, translate instruction operand into words
	// converting string->int or string->vec<WORD>
	break;
  case Bytecode::Opcode::POP:
	break;
  case Bytecode::Opcode::PEEK:
	break;
  case Bytecode::Opcode::ADD:
	break;
  case Bytecode::Opcode::SUB:
	break;
  case Bytecode::Opcode::DIV:
	break;
  case Bytecode::Opcode::MUL:
	break;
  case Bytecode::Opcode::PRINT:
	// Will need to
	break;
  }
};

vector<Word> decode(Bytecode::Instruction instruction) {
  vector<Word> words;

  if (instruction.operand.type == STRING_LITERAL)
	{
	  // Figure out the number of characters in the instructions operand
	  // then create enough words to represent the data.
	}
  else if (instruction.operand.type == INTEGER_LITERAL)
	{
	  // Convert the operand from a string into an integer then return it as a word
	}

  return words;
};


VirtualMachine::VirtualMachine(vector<Bytecode::Instruction>* bytecode) {
  
}
