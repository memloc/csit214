#include "Compiler.h"

using namespace std;
using namespace Parser;
using namespace Compiler;

Token Compiler::lex(string& sourceCode, int& index) {
    Token token;

    for (;index < sourceCode.length(); index++)
        switch (sourceCode[index]) {
            case ' ':
                if (!token.pattern.empty()) {
                    if (token.type != TokenType::STRING_LITERAL && token.type != TokenType::COMMENT) {
                        token.pattern += sourceCode[index];
                    }
                } else {
                    token.type = DELIMITER;
                    token.pattern = sourceCode[index];
                    return token;
                }

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
                if (!token.pattern.empty()) {
                    if (token.type != INTEGER_LITERAL && token.type != STRING_LITERAL) {
                        // most likely a new token, so end the current token
                        --index;
                        return token;
                    }
                } else {
                    // classify the token as a new INTEGER_LITERAL
                    token.type = INTEGER_LITERAL;
                    token.pattern += sourceCode[index];
                }
                break;

            case '(':
                if (!token.pattern.empty()) {
                    return token;
                } else {
                    token.type = TokenType::PAREN_LEFT;
                    token.pattern = sourceCode[index];
                    return token;
                }
            case ')':
                if (!token.pattern.empty()) {
                    if (token.type == STRING_LITERAL || token.type == COMMENT) {
                        token.pattern += sourceCode[index];
                    } else {
                        return token;
                    }
                }  else {
                    token.type = TokenType::PAREN_RIGHT;
                    token.pattern = sourceCode[index];
                    return token;
                }
                break;
                

            case '"':
                if (!token.pattern.empty()) {

                    // FIXME: this does not acount for escaped quotations \" in string literals
                    if (token.type == STRING_LITERAL) {
                        token.pattern += sourceCode[index];
                        return token;
                    }

                } else {
                    token.type = STRING_LITERAL;
                    token.pattern += sourceCode[index];
                }
                break;

  
            default:
                if (!token.pattern.empty()) {

                    if (token.type == IDENTIFIER) {
                        // ensure the character is alphabetic
                        if (sourceCode[index] >= 'A' && sourceCode[index] <= 'Z' || sourceCode[index] >= 'a' && sourceCode[index] <= 'z') { 
                            token.pattern += sourceCode[index];
                        } else {
                            // assume that only alphabetic character make up an identifier
                            cout << "Undefined behavior during tokenization." << endl << "Token: " << token.pattern << " + " << sourceCode[index];
                            exit(1); 
                        }
                    } else if (token.type == STRING_LITERAL) {

                        // character is contained within double quotes
                        token.pattern += sourceCode[index];

                    }
                } else {
                    // token type has not already been classified
                    // if alphabetic assume the token is an identifier
                    if (sourceCode[index] >= 'A' && sourceCode[index] <= 'Z' || sourceCode[index] >= 'a' && sourceCode[index] <= 'z') {
                        token.type = IDENTIFIER;
                        token.pattern = sourceCode[index];
                    }

                }
        }
	return token;
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

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* Compiler::compile(string& sourceCode) {
    vector<Token> tokens;

    // tokenize the input source code  
    int sourcePosition = 0;
    while (sourcePosition < sourceCode.length()) {
        tokens.push_back(Compiler::lex(sourceCode, sourcePosition));
    }

    // parse the syntax re-grouping tokens into streams of statements while ensuring the correctness
    vector<Token>* statementStream; 
    while (!tokens.empty()) {
        vector<Token>* statement = Compiler::parse(tokens);

        // Pushback tokens that comprise a single statement
        for (Token token: *statement) {
            statementStream->push_back(token);
        }
    }

    // finally translate the tokens into bytecode to be interpretted by the virtual machine
    vector<Bytecode::Instruction>* bytecode; 
    while (!statementStream->empty()) {
        bytecode->push_back(Compiler::translate(*statementStream));
    }

    return bytecode;
}
