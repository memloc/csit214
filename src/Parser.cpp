#include <map>
#include <vector>
#include <iostream>

#include "Compiler.h"
#include "Token.h"
#include "Bytecode.h"

using namespace Parser;

// Hashmap for quickly looking up language keywords
std::map<string, TokenType> LANG_KEYWORDS;

// Define the keywords of the language
void defineLanguageElements() {
	string langKeywords[] = {
		"print",
		"start",
		"end"
	};

	// Create a hashmap with a token for each keyword
	for (string keyword : langKeywords) {
		LANG_KEYWORDS.emplace(keyword, KEYWORD);
	}
}

// Look up a token in the defined keywords for the language to check if it is valid
bool keywordDefined(Token& token) {
	return (LANG_KEYWORDS.find(token.pattern)->second == KEYWORD);
}


vector<Token>* parseExpression(vector<Token>* stream, int& offset) 
{
    vector<Token>* expression = new vector<Token>;
    Token keyword = stream->at(offset++);
    expression->push_back(keyword);

    // Check the keyword to determine if the keyword requires arguments
    if (keyword.pattern == "start" || keyword.pattern == "end") {
        // Atom expressions stand on their own with no params / args
        cout << "(Atom)\tExpression Complete: " << keyword.pattern << endl;
        return expression;
    }

    // Keep track nested paren pair matching, the depth being the number pairs the offset is in
    int nestingDepth = 0; 
    int outerExpressionSize = 0; 
    int innerExpressionSize = 0;
    bool containsInt = false;
    bool containsStr = false;

    for (; offset < stream->size(); offset++) 
    {
        Token curToken = stream->at(offset);

        if (curToken.type == OPERATOR) 
        {
            // Determine the level number of nested parens we are nested within
            nestingDepth = (curToken.pattern.at(0) == '(') ? nestingDepth+1 : nestingDepth-1;
            // cout << "Depth: " << nestingDepth << endl;

            // Then we have iterated through the entire size of the expression
            if (nestingDepth == 0) 
            {

                if (outerExpressionSize == innerExpressionSize) 
                {
                    // Determine if parens must be factored into the order of operations? 
                }
                break;
            }
        }
        else 
        {
            switch (curToken.type) {
                case INTEGER_LITERAL:
                    containsInt = true;
                case ARITHMETIC_OPERATOR:
                    containsInt = true;
                    break;
                case STRING_LITERAL:
                    containsStr = true;
                    // Only check if type mismatch whenever a string literal is found
                    if (containsInt == true) {
                        cout << "Error: type mismatch." << endl;
                        exit(1);
                    }
                    break;
                default:
                    cout << "Error: Unexpected token \'" <<  curToken.pattern << "\' found in '" << keyword.pattern << "' expression";
                    exit(1);
            }
            innerExpressionSize++;
            outerExpressionSize++;
            expression->push_back(curToken);
        }
    }

    // TODO: Remove me
    cout << "\tExpression Complete: "; 
    for (Token token : *expression)
    {
        cout << token.pattern << " ";
    }
    cout << endl;

    return expression;
}



vector<Token>* parser(vector<Token>* stream) 
{
    vector<Token>* result = new vector<Token>;

    // Define all the keywords of the language before parsing
    defineLanguageElements();

    // Iterate through the token stream, branching to expression parsing whenever a keyword is found 
    for (int offset = 0; offset < stream->size(); offset++) 
    {
        // If the tokens stream is syntactically correct token at @offset will always be a keyword
        Token curToken = stream->at(offset); 
        if (keywordDefined(curToken))
        {
            // Parse the tokens within the current expression, at the current offset 
            // then continue parsing after wherever the previous expression left off
            vector<Token>* expression = parseExpression(stream, offset);

            for (Token token : *expression) {
                result->push_back(token);
            }
        }
    }



    return result;
};
