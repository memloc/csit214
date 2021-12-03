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
  
  // A pairing of an operation and operand
  struct Instruction 
  {
	Opcode operation;
	Word operand;
  };
  
}

#endif // BYTECODE_H
