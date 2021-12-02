#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>

#include "Token.h"
#include "Bytecode.h"
#include "Compiler.h"

using namespace std;

// Define the keywords of the language
void defineLanguageElements();

// Find the operator index of a nested expression
vector<int>* findOperatorIndex(vector<Parser::Token>&);

// Look up a token in the defined keywords for the language to check if it is valid
bool keywordDefined(Parser::Token&, int offset);

// parse the syntax re-grouping/re-ordering tokens into streams of statements
vector<Parser::Token>* parser(vector<Parser::Token>*);

#endif // PARSER_H