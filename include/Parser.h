#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>

#include "Lexer.h"

using namespace std;

/**
 * @brief Define the keywords of the language
 * 
 */
void defineLanguageElements();

/**
 * @brief Find the operator index of a nested expression
 * 
 * @return vector<int>
 * the pos of all Operater token with same level
 */
vector<int> findOperatorIndex(vector<Token>);

/**
 * @brief Find the index of operator in the expression where it is used first for calculation
 * 
 * @return int
 * pos of that index in list of operators' indexes
 */
int chosenOperatorIndex(vector<int>, vector<Token>);

/**
 * @brief Separate expresion into three parts: token left, token right, and token operator, respectively
 * 
 * @return vector<vector<Token>> vector of vector of token with the ordered token left, token right, and token operator, respectively
 */
vector<vector<Token>> separateExpression(int, vector<Token>);

/**
 * @brief append vectors of token into 1 token folow the order of arguments
 * 
 * @return vector<Token> vector of tokens after appended
 */
vector<Token> appendTokens(vector<Token>, vector<Token>, vector<Token>);

/**
 * @brief discard the outmost parentheses of the expression if they are reluctant
 * 
 * @return vector<Token> the new expression after discarding parentheses
 */
vector<Token> discardParen(vector<Token>);

/**
 * @brief accept 3 vectors of token in order token left, token right, and token operator and order them corectly if either one of the still have more than 1 token
 * 
 * @return vector<Token> ordered token respects to Postfix expression 
 */
vector<Token> orderTokens(vector<Token>, vector<Token>,vector<Token>);

// Look up a token in the defined keywords for the language to check if it is valid
bool keywordDefined(Token&, int offset);

// Parse the syntax re-grouping/re-ordering tokens into streams of statements
vector<Token>* parser(vector<Token>*);

#endif // PARSER_H
