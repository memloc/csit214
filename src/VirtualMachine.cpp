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



VirtualMachine::VirtualMachine(vector<Bytecode::Instruction>* bytecode) {
  
}
