#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

#include "Bytecode.h"
#include "Compiler.h"

namespace VM {

enum Exception {
  STACK_OVERFLOW,
  STACK_UNDERFLOW,
};

using namespace std;

enum class WordType : uint8_t {
  INT32_T,
  CHAR32_T,
  CHAR_T,
};

/* Extra 16-bits left-over to put inside the WORD
enum class WordFlags:uint8_t {};
*/

/*
 * @brief A fixed size unit of memory to store data (64-bits)
 * The intended interpretation of the data being the WordType.
 */
typedef struct Word {
  WordType type;
  union {
    int32_t asInt32;
    uint32_t asUInt32;
    struct asChar32 {
      int8_t $ch1; // 'o'
      int8_t $ch2; // 'o'
      int8_t $ch3; // 'p
      int8_t $ch4; // 's' Must null terminate '\0'
    } asChar32;
  } memory;
} Word;

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

private:
  // convert the data in an instruction into a word
  vector<Word> convert(Bytecode::Instruction);
};

} // namespace VM

#endif // VIRTUAL_MACHINE_H
