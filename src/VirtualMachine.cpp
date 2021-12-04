#include "Bytecode.h"
#include "Compiler.h"
#include "Token.h"
#include "VirtualMachine.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <string>

using namespace VM;


// execute until finished 
void VirtualMachine::run() {
  	while (!bytecode->empty() && !halt) {
		load();
		step();
  	}
}

void VirtualMachine::step() {
	// Load the instruction pointer	
	if (!bytecode->empty()) {
		ip = &bytecode->back();
	} else {
		exit(1);
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
  case Bytecode::Opcode::ADD: 
  {
	  Bytecode::Word a = data.top();
	  data.pop();
	  Bytecode::Word b = data.top();
	  data.pop();
	  
	  Bytecode::Word c;
	  c.type = Bytecode::WordType::INT32_T;
	  c.memory.asInt32 =  b.memory.asInt32 + a.memory.asInt32;
  }
    break;
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
  case Bytecode::Opcode::PRINT: ;
	cout << "----- VM OUTPUT -----"<< endl;
	for (int32_t i = 1; i != ip->operand.memory.asInt32; i++) {
		Bytecode::Word word = data.top();
		data.pop();

		if (word.type == Bytecode::WordType::INT32_T) {
			cout << word.memory.asInt32;
		} else if (word.type == Bytecode::WordType::CHAR32_T) {
			cout << word.memory.asChar32.c0 
					<< word.memory.asChar32.c1
					<< word.memory.asChar32.c2
					<< word.memory.asChar32.c3;
		}
	}
	cout << endl <<  "---------------------" << endl;
	break;
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