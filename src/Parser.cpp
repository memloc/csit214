#include <map>
#include <vector>
#include <iostream>

#include "Lexer.h"

// Hashmap for quickly looking up language keywords
std::map<string, TokenType> LANG_KEYWORDS;

// Define the keywords of the language
void defineLanguageElements() {
  string langKeywords[] = {"print", "start", "end"};

  // Create a hashmap with a token for each keyword
  for (string keyword : langKeywords) {
    LANG_KEYWORDS.emplace(keyword, KEYWORD);
  }
}

// Look up a token in the defined keywords for the language to check if it is valid
bool keywordDefined(Token &token) {
  return (LANG_KEYWORDS.find(token.pattern)->second == KEYWORD);
}

vector<int> *findOperatorIndex(vector<Token> &expression) {
  vector<int> *operator_index = new vector<int>;
  for (size_t i = 0; i < expression.size(); i++) {
    if (expression.at(i).type == INTEGER_LITERAL) {
      operator_index->push_back(++i);
    } else if (expression.at(i).type == PAREN_LEFT) {
      int count = 1;
      for (size_t j = i + 1; j < expression.size(); j++) {
        if (expression.at(j).type == PAREN_LEFT) {
          count++;
        } else if (expression.at(j).type == PAREN_RIGHT) {
          count--;
        }

        if (count == 0) {
          operator_index->push_back(j + 1);
          i = j + 1;
          break;
        }
      }
    }
  }
  operator_index->pop_back();
  return operator_index;
}

vector<Token> *parseExpression(vector<Token> *stream, int &offset) {
  vector<Token> *expression = new vector<Token>;
  Token keyword = stream->at(offset);

  // Check the keyword to determine if the keyword requires arguments
  if (keyword.pattern == "start" || keyword.pattern == "end") {
    // Atom expressions stand on their own with no params / args
    cout << "\n(Atom)\tExpression Complete: " << keyword.pattern << endl;
    expression->push_back(keyword);
    return expression;
  }

  // Otherwise skip the keyword token and parse the expression
  offset++;

  // Keep track of the number of nested parens (the depth being the current number pairs nested parens)
  int nestingDepth = 0;
  bool containsInt = false;
  bool containsStr = false;

  // Before checking the syntax for the entire expression ensure it begins with an open paren
  if (stream->at(offset).type != PAREN_LEFT) {
    cout << "Error: Unexpected token \'" << stream->at(offset).pattern
         << "\' found where '(' expected." << endl;
    exit(1);
  }

  for (; offset < stream->size(); offset++) {
    Token curToken = stream->at(offset);

    switch (curToken.type) {

    case PAREN_LEFT:
      nestingDepth++;
      if (nestingDepth > 1) {
        expression->push_back(curToken);
      }
      break;

    case PAREN_RIGHT:
      nestingDepth--;
      if (nestingDepth >= 1) {
        expression->push_back(curToken);
      }
      break;

    case INTEGER_LITERAL:
      containsInt = true;
      expression->push_back(curToken);
      break;

    case ARITHMETIC_OPERATOR:
      containsInt = true;
      expression->push_back(curToken);
      break;

    case STRING_LITERAL:
      containsStr = true;
      expression->push_back(curToken);
      break;

    case KEYWORD:
      cout << "Error: Unexpected token '" << curToken.pattern
           << "' found inside of a '" << keyword.pattern << "' statement. "
           << endl;
      exit(1);

    default:
      cout << "Error: Unexpected token \'" << curToken.pattern
           << "\' found in '" << keyword.pattern << "' expression";
      exit(1);
    };

    // If matched the last pair of parens then exit
    if (nestingDepth == 0) {
      // Check for type mismatch on exit
      if (containsInt == true && containsStr == true) {
        cout << "Error: type mismatch found inside '" << keyword.pattern << "' statement " << endl;
        exit(1);
      }
      break;
    }
  }

  // TODO: Remove me
  cout << "\nExpression: ";
  for (Token token : *expression) {
    cout << token.pattern << " ";
  }
  cout << endl;

  if (expression->size() > 2) {
    vector<int> *operatorIndexes = findOperatorIndex(*expression);
    // TODO: Remove me
    cout << "Operator Indexes\n";
    for (int index : *operatorIndexes) {
      cout << "  index[" << index << "]: " << expression->at(index).pattern
           << "\n";
    }
  }

  // return expression postfix notation following order of operations
  // Add the keyword for the expression to the end (i.e 1 2 + print)
  expression->push_back(keyword);
  return expression;
}

vector<Token> *parser(vector<Token> *stream) {
  vector<Token> *result = new vector<Token>;

  if (stream->front().pattern != "start" || stream->back().pattern != "end")
	{
	  exit(1);
	}

  // Define all the keywords of the language before parsing
  defineLanguageElements();

  // Iterate through the token stream, branching to expression parsing whenever
  // a keyword is found
  for (int offset = 0; offset < stream->size(); offset++) {
    // If the tokens stream is syntactically correct token at @offset will
    // always be a keyword
    Token curToken = stream->at(offset);

    if (keywordDefined(curToken)) {
      // Parse the tokens within the current expression, at the current offset
      // then continue parsing after wherever the previous expression left off
      vector<Token> *expression = parseExpression(stream, offset);

      for (Token token : *expression) {
        result->push_back(token);
      }
    } else {
	  cout << "Fatal Error During Parsing";
	  exit(1);
	}
  }

  return result;
};
