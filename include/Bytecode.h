#ifndef BYTECODE_H
#define BYTECODE_H

#include <iostream>

#include "Token.h"

namespace Bytecode 
{
  
  enum class Opcode:int8_t 
    {
	  NOP,
	  PUSH,
	  POP,
	  PEEK,
	  ADD,
	  SUB,
	  DIV,
	  MUL,
	  PRINT,
    };
  
  
  enum class WordType : uint8_t {
	INT32_T,
	CHAR32_T,
  };
  
	enum class WordFlag:uint8_t {
	};
  
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
		  int8_t c0;
		  int8_t c1;
		  int8_t c2;
		  int8_t c3;
	  } asChar32;
	} memory;
  } Word;
  
  // A pairing of an operation and operand
  struct Instruction 
  {
	Opcode operation;
	Word operand;
  };
  
}

#endif // BYTECODE_H
