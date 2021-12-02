#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

#include <vector>
#include <iostream>

using namespace std;

// produces a token stream from the input source code
vector<Token> lex(string&);

void completedToken(Token&, vector<Token>&);

#endif // LEXER_H