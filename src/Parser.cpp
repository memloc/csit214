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

//(( (1+2)*3-4+(2*(3-5))))
vector<Token> discardParen(vector<Token> expression) {
  vector<Token> newExpression;
  int depth = 0;
  for (auto i = 0; i < expression.size(); i++) {
    if (expression.at(i).type == PAREN_LEFT) {
      depth++;
    } else if (expression.at(i).type == PAREN_RIGHT) {
      depth--;
    }

    if (depth == 0) {
      // return old expression
      if (i < expression.size() - 1) {
        return expression;
      } else {
        for (auto j = 1; j < expression.size() - 1; j++) {
          newExpression.push_back(expression.at(j));
        }
		    return discardParen(newExpression);
      }
    }
  }
  return expression;
}

vector<int> findOperatorIndex(vector<Token> expression) {
  vector<int> operator_index;
  for (size_t i = 0; i < expression.size(); i++) {
    if (expression.at(i).type == INTEGER_LITERAL) {
      operator_index.push_back(++i);
    } else if (expression.at(i).type == PAREN_LEFT) {
      int count = 1;
      for (size_t j = i + 1; j < expression.size(); j++) {
        if (expression.at(j).type == PAREN_LEFT) {
          count++;
        } else if (expression.at(j).type == PAREN_RIGHT) {
          count--;
        }

        if (count == 0) {
          operator_index.push_back(j + 1);
          i = j + 1;
          break;
        }
      }
    }
  }
  operator_index.pop_back();
  return operator_index;
}

int chosenOperatorIndex(vector<int> operator_index, vector<Token> expression) {
  int index = operator_index[0];
  for (auto i = 0; i < operator_index.size() - 1; i++) {
    if ((expression.at(index).pattern.compare("*") == 0 ||
         expression.at(index).pattern.compare("/") == 0) &&
        (expression.at(operator_index.at(i + 1)).pattern.compare("+") == 0 ||
         expression.at(operator_index.at(i + 1)).pattern.compare("-") == 0)) {
      index = operator_index[i + 1];
    }
  }
  return index;
}

vector<vector<Token>> separateExpression(int chosenIndex,
                                         vector<Token> expression) {
  vector<vector<Token>> separatedExpression;
  vector<Token> tokenL; // left
  vector<Token> tokenR; // right
  vector<Token> tokenO; // operator
  for (auto i = 0; i < chosenIndex; i++) {
    tokenL.push_back(expression.at(i));
  }

  for (auto i = chosenIndex + 1; i < expression.size(); i++) {
    tokenR.push_back(expression.at(i));
  }
  tokenO.push_back(expression.at(chosenIndex));

  separatedExpression.push_back(tokenL);
  separatedExpression.push_back(tokenR);
  separatedExpression.push_back(tokenO);
  return separatedExpression;
}

vector<Token> appendTokens(vector<Token> tokenL, vector<Token> tokenR, vector<Token> tokenO) {
  vector<Token> appendedTokens;
  for (Token token : tokenL) {
    appendedTokens.push_back(token);
  }
  for (Token token : tokenR) {
    appendedTokens.push_back(token);
  }
  appendedTokens.push_back(tokenO.at(0));
  return appendedTokens;
}

vector<Token> orderTokens(vector<Token> tokenL, vector<Token> tokenR,
                          vector<Token> tokenO) {
                            const int LEFT = 0;
                            const int RIGHT = 1;
                            const int OPERATOR = 2;
	if (tokenL.size() == 1 && tokenR.size() == 1) {
		return appendTokens(tokenL, tokenR, tokenO);
	}else if (tokenL.size() > 1 && tokenR.size() == 1) {
    // ((  (1+2)*3-4+(2*(3-5))  ))
		vector<Token> newTokenL = discardParen(tokenL);
		vector<int> operatorIndex = findOperatorIndex(newTokenL);
		int chosenIndex = chosenOperatorIndex(operatorIndex, newTokenL);
		vector<vector<Token>> separatedExpression = separateExpression(chosenIndex, newTokenL);
		return appendTokens(orderTokens(separatedExpression.at(LEFT), separatedExpression.at(RIGHT), separatedExpression.at(OPERATOR)), tokenR, tokenO);
	}else if (tokenR.size() > 1 && tokenL.size() == 1) {
		vector<Token> newTokenR = discardParen(tokenR);
		vector<int> operatorIndex = findOperatorIndex(newTokenR);
		int chosenIndex = chosenOperatorIndex(operatorIndex, newTokenR);
		vector<vector<Token>> separatedExpression = separateExpression(chosenIndex, newTokenR);
		return appendTokens(tokenL, orderTokens(separatedExpression.at(LEFT), separatedExpression.at(RIGHT), separatedExpression.at(OPERATOR)), tokenO);
	}else {
		vector<Token> newTokenL = discardParen(tokenL);
		vector<int> operatorIndexL = findOperatorIndex(newTokenL);
		int chosenIndexL = chosenOperatorIndex(operatorIndexL, newTokenL);
		vector<vector<Token>> separatedExpressionL = separateExpression(chosenIndexL, newTokenL);

		vector<Token> newTokenR = discardParen(tokenR);
		vector<int> operatorIndexR = findOperatorIndex(newTokenR);
		int chosenIndexR = chosenOperatorIndex(operatorIndexR, newTokenR);
		vector<vector<Token>> separatedExpressionR = separateExpression(chosenIndexR, newTokenR);
		return appendTokens(orderTokens(separatedExpressionL.at(LEFT), separatedExpressionL.at(RIGHT), separatedExpressionL.at(OPERATOR)), orderTokens(separatedExpressionR.at(LEFT), separatedExpressionR.at(RIGHT), separatedExpressionR.at(OPERATOR)), tokenO);
	}
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
    int LEFT;

    vector<Token> newExpression = discardParen(*expression);
    vector<int> operatorIdex = findOperatorIndex(newExpression);
    int chosenIndex = chosenOperatorIndex(operatorIdex, newExpression);
    vector<vector<Token>> separatedExpression = separateExpression(chosenIndex, newExpression);
    vector<Token> orderedTokens = orderTokens(separatedExpression.at(0), separatedExpression.at(1), separatedExpression.at(2));


    // TODO: Remove me
    cout << "Operator Indexes\n";
    for (Token token : orderedTokens) {
      cout << "Order: " << token.pattern << "\n";
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
	  cout << "Error: Keyword Undefined." << endl;
	  exit(1);
	}
  }

  return result;
};
