#include "../include/Compiler.h"


Parser::Token lex(string& source, int& index) {

    index = 4;

    Parser::Token temp;
    temp.type = Parser::TokenType::Number
    temp.pattern = "";

    string tmp = "";
    for (int i = 0; i < code.length; i++) {
        index++;

        switch (code[i]) {
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
                if (temp.type == Parser::TokenType::INTEGER_LITERAL) {
                    tmp += code[i];
                } else if (temp.type == NULL) {
                    temp.type = Parser::TokenType::INTEGER_LITERAL;
                    tmp += code[i];
                } else {
                    return temp;
                }




            case '(';
                if (temp.type == NULL) {
                    temp.pattern = code[i];
                    temp.type = Parser::TokenType::PAREN_LEFT;
                    return temp;
                }
            case ')';
                if (temp.type == NULL) {
                    temp.pattern = code[i];
                    temp.type = Parser::TokenType::PAREN_RIGHT;
                    return temp;
                }
                

            case '"':
                if (temp.type == Parser::TokenType::STRING_LITERAL) {
                    tmp += code[i];
                    temp.pattern = tmp;
                    return temp;
                } else if (temp.type == NULL) {
                    temp.type = Parser::TokenType::STRING_LITERAL;
                    tmp += code[i];
                } else {
                    return temp;
                }

  
            default:
                if (temp.type == NULL) {
                    temp.type = Parser::TokenType::IDENTIFIER;
                    tmp += code[i];
                }
                if (temp.type == Parser::TokenType::STRING_LITERAL) {




                }

                if (temp.type == Parser::TokenType::IDENTIFIER) {
                    if (tmp == "print") {
                        temp.pattern = tmp;
                        return tmp;
                    } else if (index == 4 && tmp != "start") {
                        exit(1);
                    }
                }

                tmpString += code[i];
        }
    }
}

vector<Parser::Token>* parse(string& source) {
    vector<Parser::Token> tokens;

    int sourcePosition = 0;
    
    while (index < source.length) {
        tokens.push_back(lex(source), sourcePosition);
    }
}

// translate tokens from the token stream into instructions in bytecode representation
Bytecode::Instruction translate(vector<Parser::Token>&);

// performs lexing, parsing, and translation into the bytecode representation of the program
vector<Bytecode::Instruction>* compile(string &);