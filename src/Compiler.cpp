#include "../include/Compiler.h"

using namespace std;
using namespace Parser;
using namespace Compiler;

void completedToken(Token &token, vector<Token> &tokens)
{
	if (token.type != WHITE_SPACE)
	{
		tokens.push_back(token);
	}

	token.type = WHITE_SPACE;
	token.pattern.erase();
}

vector<Token> lex(string &sourceCode)
{
	Token curToken{WHITE_SPACE, ""};
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
				curToken.type = OPERATOR;
				curToken.pattern = c;
				completedToken(curToken, tokens); //token{WHITE_SPACE, ""}
			}
			else
			{
				curToken.pattern += c;
			}
			break;

		case ';':
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


vector<Token>* Compiler::parse(vector<Token>& tokenStream) {
    vector<Token>* statement;

    // iterate through each token creating statements, and checking syntax
    for (Token token : tokenStream) {
        switch(token.type) {
            case KEYWORD:
            case DELIMITER:
            case IDENTIFIER:
            case OPERATOR:
            case COMMENT:
            case PAREN_LEFT:
                // if statement begins with identifier and contains assume this is a function statement, so it is syntactically correct 
                if (statement->front().type == IDENTIFIER) {
                    // statement = ['IDENTIFIER':'print'],['PAREN_LEFT':'(']
                    statement->push_back(token);
                } else if (statement->front().type == COMMENT) {
                    // then this statement is a still a comment
                    statement->push_back(token);
                }
            case PAREN_RIGHT:
            case INTEGER_LITERAL:
            case STRING_LITERAL:
            break;
            //...
        }
    }

    return statement;
}

// translate tokens from the token stream into instructions in bytecode representation
Bytecode::Instruction Compiler::translate(vector<Token>& statementStream) {
    Bytecode::Instruction instruction;

    // create an instruction from one or more tokens

    return instruction;
}

// Commented by @thpham1997
// performs lexing, parsing, and translation into the bytecode representation of the program
// vector<Bytecode::Instruction>* Compiler::compile(string& sourceCode) {
//     vector<Token> tokens;

//     // tokenize the input source code  
//     int sourcePosition = 0;
//     while (sourcePosition < sourceCode.length()) {
//         tokens.push_back(Compiler::lex(sourceCode, sourcePosition));
//     }

//     // parse the syntax re-grouping tokens into streams of statements while ensuring the correctness
//     vector<Token>* statementStream; 
//     while (!tokens.empty()) {
//         vector<Token>* statement = Compiler::parse(tokens);

//         // Pushback tokens that comprise a single statement
//         for (Token token: *statement) {
//             statementStream->push_back(token);
//         }
//     }

//     // finally translate the tokens into bytecode to be interpretted by the virtual machine
//     vector<Bytecode::Instruction>* bytecode; 
//     while (!statementStream->empty()) {
//         bytecode->push_back(Compiler::translate(*statementStream));
//     }

//     return bytecode;
// }
