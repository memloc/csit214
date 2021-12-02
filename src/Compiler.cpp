#include "../include/Compiler.h"
#include "Bytecode.h"
#include "Token.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace Parser;
using namespace Compiler;


void completedToken(Token &token, vector<Token> &tokens)
{
	if (token.type != WHITE_SPACE)
	{
		tokens.push_back(token);

		// TODO: Remove me, for debugging
		cout << "Generated Token: { '" << token.pattern << "', '" << token.type << "' }" << endl;
	}


	token.type = WHITE_SPACE;
	token.pattern.erase();
}

vector<Token> Compiler::lex(string &sourceCode)
{
	Token curToken = { 
		.type = WHITE_SPACE,
		.pattern = ""
	};

	vector<Token> tokens;
	for (char c : sourceCode)
	{
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (curToken.type == WHITE_SPACE)
			{
				curToken.type = INTEGER_LITERAL;
				curToken.pattern = c;
			}
			else if (curToken.type == STRING_LITERAL || curToken.type == INTEGER_LITERAL || curToken.type == IDENTIFIER)
			{
				curToken.pattern += c;
			}
			else if (curToken.type == ARITHMETIC_OPERATOR)
			{
				completedToken(curToken, tokens);
				curToken.type = INTEGER_LITERAL;
				curToken.pattern += c;
			}
			break;

		case '(':
		case ')':
			if (curToken.type != STRING_LITERAL)
			{
				completedToken(curToken, tokens);
				curToken.type = (c == '(') ? PAREN_LEFT : PAREN_RIGHT;
				curToken.pattern = c;
				completedToken(curToken, tokens); //token{WHITE_SPACE, ""}
			}
			else
			{
				curToken.pattern += c;
			}
			break;

		case ';':
		case '\n':
		case ' ':
			if (curToken.type == STRING_LITERAL)
			{
				curToken.pattern += c;
			}
			else if (curToken.type != WHITE_SPACE) //anything else not WHITE_SPACE or STRING_LITERAL gonna be pushed back
			{
				completedToken(curToken, tokens); //token{WHITE_SPACE, ""}
			}
			break;
		case '"':
			if (curToken.type != STRING_LITERAL)
			{
				completedToken(curToken, tokens); //token{WHITE_SPACE, ""}
				curToken.pattern += c;
				curToken.type = STRING_LITERAL;
			}
			else
			{
				curToken.pattern += c;
				completedToken(curToken, tokens);//token{WHITE_SPACE, ""}
			}
			break;

		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			if (curToken.type != STRING_LITERAL)
			{
				completedToken(curToken, tokens);
				curToken.type = ARITHMETIC_OPERATOR;
				curToken.pattern = c;
				completedToken(curToken, tokens);
			}
			else
			{
				curToken.pattern += c;
				tokens.push_back(curToken);
			}
			break;
		default:
			if (curToken.type == STRING_LITERAL)
			{
				curToken.pattern += c;
			}
			else
			{
				curToken.pattern += c;
				curToken.type = KEYWORD;
			}

			break;
		}
	}

	return tokens;
}

// translate tokens from the token stream into instructions in bytecode representation
Bytecode::Instruction Compiler::translate(vector<Token>& statementStream) {
    Bytecode::Instruction instruction;

    // create an instruction from one or more tokens


    return instruction;
}

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* Compiler::compile(string& sourceCode) {
	cout << "\n======== Generating Tokens ========\n" << endl;
    vector<Token> tokens = lex(sourceCode);

	cout << "\n======== Parsing Expressions ========\n" << endl;
	vector<Token>* stream = parser(&tokens);

	cout << "\n======== Token Stream ========\n";
    for (Token token : *stream) {
        cout << token.pattern << " ";
    }
    cout << "\n\n";

    vector<Bytecode::Instruction>* bytecode; 
    return bytecode;
}
