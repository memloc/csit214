#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <stack>
#include <vector>
#include <iostream>

#include "Bytecode.h"

namespace VM {

  using namespace std;

  enum class WordType:uint8_t {
    CHAR_T, 
    INT_T,
  };

  /**
   * @brief A fixed size unit of data (64-bits)
   * @param type the intended interpretation of the data, one of WordType.
   */
  typedef struct Word {
      WordType type;

      union {
        int8_t asChar;
        int32_t asInt;
      };
  } Word;

  class VirtualMachine {
  private:
    // keep track of program execution progress (program counter)
    int32_t counter; 

    // stack pointer
    Word *sp;
    stack<Word> data;

    // instruction pointer
    Bytecode::Instruction *ip; 
    vector<Bytecode::Instruction>* code;

    // halt execution flag
    bool halt; 

  private:
    // execute a single instruction
    void step(Bytecode::Instruction);

  public:
    void load(/* bytecode source code */);
    void run();
  };

}

#endif // VIRTUAL_MACHINE_H
