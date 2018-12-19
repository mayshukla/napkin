#ifndef NAPKIN_LEXER_H_
#define NAPKIN_LEXER_H_

#include <exception>
#include <unordered_map>
#include <vector>

#include "token.h"

namespace napkin {

class LexerException: public std::exception {
  virtual const char* what() const throw() {
    return "napkin lexer error occured";
  }
};

class Lexer {
public:
  Lexer(std::string t_source) : source(t_source) {
    sourceLength = source.size();
    lexTokens();
  }
  std::vector<napkin::Token> getTokens();
  bool safeToParse();

private:
  std::string source;
  unsigned int sourceLength;
  std::vector <napkin::Token> tokens;
  unsigned int startPosition = 0; // Index of start of current token in line
  unsigned int currentPosition = 0; // Index of current character
  unsigned int line = 1; // Line number the lexer is on (for error messages)
  bool hadError = false;
  KeywordToTokenTypeMap keywordToTokenTypeMap;

  void lexTokens();
  void lexToken();
  void number();
  void imNumber();
  void identifier();
  char advance();
  bool match(char expected);
  char peek(unsigned int n);
  void addToken(TokenType tokenType, std::string lexeme);
  bool isDigit(char c);
  bool isChar(char c);
  bool isAtEnd();
};

} // namespace napkin

#endif
