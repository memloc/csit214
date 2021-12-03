#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

#include "Bytecode.h"
#include "Compiler.h"

using namespace Bytecode;

namespace VM {

enum Exception {
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
};

using namespace std;


class VirtualMachine {
private:
  // keep track of program execution progress (program counter)
  int32_t counter;

  // Stack pointer
  Word *sp;
  stack<Word> data;

  // Instruction pointer
  Bytecode::Instruction *ip;
  vector<Bytecode::Instruction> *bytecode;

  // Halt execution flag
  bool halt;

public:
  VirtualMachine(vector<Bytecode::Instruction> *);
  void run();

private:
  // load a single instruction
  void load(Bytecode::Instruction);
  // execute a single instruction
  void step();
};

} // namespace VM

#endif // VIRTUAL_MACHINE_H
