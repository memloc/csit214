#include "Bytecode.h"
#include "Compiler.h"
#include "Token.h"
#include "VirtualMachine.h"
#include <cstdio>
#include <string>

using namespace VM;


// execute until finished 
void VirtualMachine::run() {
  while (!bytecode->empty()) {
	load();
  }
}

void VirtualMachine::step(){
  // Execute the next instruction and increment the counter
  counter++;
	if (data.empty() && bytecode->empty()) {
		cout << "Empty";
		exit(1);
	}
  // Execute the instruciton at the instruction pointer
  switch(ip->operation) {
  case Bytecode::Opcode::NOP:
	break;
  case Bytecode::Opcode::PUSH:
	break;
  case Bytecode::Opcode::POP:
	break;
  case Bytecode::Opcode::PEEK:
	// Unimplemented
	break;
  case Bytecode::Opcode::ADD:
	if (data.top().type == WordType::INT32_T) {
	};
	break;
  case Bytecode::Opcode::SUB:
	if (data.top().type == WordType::INT32_T) {
	};
	break;
  case Bytecode::Opcode::DIV:
	if (data.top().type == WordType::INT32_T) {
	};
	break;
  case Bytecode::Opcode::MUL:
	if (data.top().type == WordType::INT32_T) {
	};
	break;
  case Bytecode::Opcode::PRINT:
	if (data.top().type == WordType::INT32_T) {
	};
	break;
  }
};

// Load the current instruction
void VirtualMachine::load() {
  if (!bytecode->empty()) {
	// Set the current instruction
	ip = &bytecode->back();

	// Debug Printing
	if (ip->operand.type == Bytecode::WordType::CHAR32_T) {

		cout << "Loading CHAR32_T: ";
		cout << ip->operand.memory.asChar32.c0 
			<< ip->operand.memory.asChar32.c1 
			<< ip->operand.memory.asChar32.c2 
			<< ip->operand.memory.asChar32.c3 
			<< endl;

	} else if (ip->operand.type == Bytecode::WordType::INT32_T) {

		cout << "Loading INT32_T: " << ip->operand.memory.asInt32 << endl;

	}

	// Get rid of the previous instruction
	bytecode->pop_back();
  }
};

VirtualMachine::VirtualMachine(vector<Bytecode::Instruction>* bytecode) {
	this->bytecode = bytecode;
}
