#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;

enum TokenType 
{
  WHITE_SPACE,
  KEYWORD,
  IDENTIFIER,
  STRING_LITERAL,
  INTEGER_LITERAL,
  PAREN_LEFT,
  PAREN_RIGHT,
  ARITHMETIC_OPERATOR,
  OPERATOR,
  COMMENT,
};

/**
 * @brief A pairing of a TokenType and Lexeme, the lexeme being a sequence
 * of characters corresponding to a pattern with predefined semantic meaning.
 */
struct Token 
{
  TokenType type;
  string pattern;
};

#endif // TOKEN_H