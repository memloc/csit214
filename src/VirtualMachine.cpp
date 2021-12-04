#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <string>

#include "../include/Bytecode.h"
#include "../include/Compiler.h"
#include "../include/Token.h"
#include "../include/VirtualMachine.h"

using namespace VM;


// execute until finished 
void VirtualMachine::run() {
	cout << "===== STACK TOP =====" << endl;
  	while (!bytecode->empty() && !halt) {
		load();
		step();
  	}
	cout << "===== STACK BOT =====" << endl;
}

void VirtualMachine::step() {
	// Load the instruction pointer	
	if (!bytecode->empty()) {
		ip = &bytecode->back();
	} else {
		return;
	}

  // Execute the instruciton at the instruction pointer
  switch (ip->operation) {
  case Bytecode::Opcode::NOP:
	// No operation
    break;
  case Bytecode::Opcode::PUSH:
  	data.push(ip->operand);
    break;
  case Bytecode::Opcode::POP:
	if (data.empty()) {
		halt=true;
	} else {
		data.pop();
	}
    break;
  case Bytecode::Opcode::PEEK:
	// Unimplemented
    break;
  case Bytecode::Opcode::ADD: {
	  Bytecode::Word a = data.top();
	  data.pop();
	  Bytecode::Word b = data.top();
	  data.pop();

	  Bytecode::Word c;
	  c.type = Bytecode::WordType::INT32_T;
	  c.memory.asInt32 =  b.memory.asInt32 + a.memory.asInt32;
	  data.push(c);
    break;
  }
  case Bytecode::Opcode::SUB: {
	  Bytecode::Word a = data.top();
	  data.pop();
	  Bytecode::Word b = data.top();
	  data.pop();
	  
	  Bytecode::Word c;
	  c.type = Bytecode::WordType::INT32_T;
	  c.memory.asInt32 = a.memory.asInt32 - a.memory.asInt32;
	  data.push(c);
  }
    break;
  case Bytecode::Opcode::DIV: {
	  Word a = data.top();
	  data.pop();
	  Word b = data.top();
	  data.pop();
	  
	  Bytecode::Word c;
	  c.type = Bytecode::WordType::INT32_T;
	  c.memory.asInt32 = a.memory.asInt32 - b.memory.asInt32;
	  c.memory.asInt32 = b.memory.asInt32 / a.memory.asInt32;
	  data.push(c);
  }
    break;
  case Bytecode::Opcode::MUL: {
	  Bytecode::Word a = data.top();
	  data.pop();
	  Bytecode::Word b = data.top();
	  data.pop();
	  
	  Bytecode::Word c;
	  c.type = Bytecode::WordType::INT32_T;
	  c.memory.asInt32 =  b.memory.asInt32 * a.memory.asInt32;
	  data.push(c);
 	}
    break;
  case Bytecode::Opcode::PRINT: {
	size_t NUM_PRINT_OPERATIONS= 1; 
	cout << "----- VM OUTPUT -----"<< endl;
	if (data.top().type == Bytecode::WordType::INT32_T) {
		Bytecode::Word word = data.top();
		data.pop();
		cout << word.memory.asInt32;
	} else if (data.top().type == Bytecode::WordType::CHAR32_T) {
		for (int32_t i = NUM_PRINT_OPERATIONS; i != ip->operand.memory.asInt32; i++) {
			Bytecode::Word word = data.top();
			data.pop();
			if (word.type == Bytecode::WordType::CHAR32_T) {
				cout << word.memory.asChar32.c0 
						<< word.memory.asChar32.c1
						<< word.memory.asChar32.c2
						<< word.memory.asChar32.c3;
			}
		}
	}
	cout << endl <<  "---------------------" << endl;
  	}
	break;
	default:;
  }
};

// Load the current instruction
void VirtualMachine::load() {
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