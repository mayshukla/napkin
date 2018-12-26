#ifndef NAPKIN_PARSER_H_
#define NAPKIN_PARSER_H_

#include <vector>

#include "AST.h"
#include "token.h"

namespace napkin {

/**
 * Recursive descent parser
 */
class Parser {
public:
  Parser(std::vector<Token> t_tokens) : tokens(t_tokens){};
  Expr *parse();

private:
  std::vector<Token> tokens;
  unsigned int current = 0; // index of current token

  // Each of these methods correspond to a rule in ebnf.txt
  Expr *expr();
  Expr *equality();
  Expr *comparison();
  Expr *addition();
  Expr *multiplication();
  Expr *unary();
  Expr *primary();

  // Helper methods
  bool match(TokenType type);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
};

} // namespace napkin

#endif
