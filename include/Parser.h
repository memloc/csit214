#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>

#include "Token.h"
#include "Bytecode.h"
#include "Compiler.h"

// Define the keywords of the language
void defineLanguageElements();

// Look up a token in the defined keywords for the language to check if it is valid
bool keywordDefined(Parser::Token&, int offset);

// parse the syntax re-grouping/re-ordering tokens into streams of statements
std::vector<Parser::Token>* parser(std::vector<Parser::Token>*);

#endif // PARSER_H