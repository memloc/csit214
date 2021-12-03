#include "Bytecode.h"
#include "Compiler.h"
#include "Token.h"
#include "VirtualMachine.h"
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>

using namespace VM;


// execute until finished 
void VirtualMachine::run() {
	cout << "====== STACK BOT ======" << endl;
  while (!bytecode->empty()) {
	load();
  }
  cout << "====== STACK TOP ======" << endl;
  cout << "\n\n";
  while (!data.empty()) {
	step();
  }
}

void VirtualMachine::step(){
  	// Execute the next instruction and increment the counter
	if (data.empty() && bytecode->empty()) {
		cout << "ERROR: STACK UNDERFLOW." << endl;
		exit(1);
	}


  // Execute the instruciton at the instruction pointer
  switch(ip->operation) {
  case Bytecode::Opcode::NOP:
	break;
  case Bytecode::Opcode::PUSH:
	data.push(ip->operand);
	break;
  case Bytecode::Opcode::POP:
	if (data.empty()) 
	{
		halt = true;
	}
    else 
	{
		data.pop();
	}
	break;
  case Bytecode::Opcode::PEEK:
	// Load the top of the stack into register 1

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
		for (int n = 0; n < data.top().memory.asInt32; n++) {
		}
	}

	break;
  }
};

// Load the current instruction
void VirtualMachine::load() {
    counter++;
  if (!bytecode->empty()) {
	// Set the current instruction
	ip = &bytecode->back();

	loaderDebugPrint();

	// Get rid of the previous instruction
	bytecode->pop_back();
  }
};

VirtualMachine::VirtualMachine(vector<Bytecode::Instruction>* bytecode) {
	this->bytecode = bytecode;
	counter=0;
}

// messy printing for debugging 
void VirtualMachine::loaderDebugPrint() {
	switch (ip->operation) {
        case Bytecode::Opcode::NOP:
			cout << "NOP: " << endl;
			break;
        case Bytecode::Opcode::PUSH:
			if (ip->operand.type == Bytecode::WordType::CHAR32_T)
			{
				;
				cout << "PUSH\tCHAR_32\t  " << ip->operand.memory.asChar32.c0
					<< ip->operand.memory.asChar32.c1
					<< ip->operand.memory.asChar32.c2
					<< ip->operand.memory.asChar32.c3 << endl;
			}
			else if (ip->operand.type == Bytecode::WordType::INT32_T) 
			{
				cout << "PUSH\tINT_32\t  " << ip->operand.memory.asInt32 << "\t" << endl;
			}
			break;
        case Bytecode::Opcode::POP:
			cout << "POP" << endl;
			break;
        case Bytecode::Opcode::PEEK:
			cout << "PEEK" << endl;
			break;
        case Bytecode::Opcode::ADD:
			cout << "ADD" << endl;
			break;
        case Bytecode::Opcode::SUB:
			cout << "SUB" << endl;
			break;
        case Bytecode::Opcode::DIV:
			cout << "DIV" << endl;
			break;
        case Bytecode::Opcode::MUL:
			cout << "MUL" << endl;
			break;
        case Bytecode::Opcode::PRINT:
			cout << "PRINT\t(x" << ip->operand.memory.asInt32 << ")" << endl;
          break;
        }
}