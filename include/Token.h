#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

namespace Parser {

  using namespace std;

  enum TokenType {
    DELIMITER,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    COMMENT,
  }; 
  
  /**
   * @brief A pairing of a TokenType and Lexeme, the lexeme being a sequence
   * of characters corresponding to a pattern with predefined semantic meaning.
   */
  struct Token {
    TokenType type;
    string pattern;
  };

}

#endif // TOKEN_H