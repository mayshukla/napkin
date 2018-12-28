#include "parser.h"

namespace napkin {

/**
 * Constructs AST and returns root node.
 */
Expr *Parser::parse() {
  return expr();
}

/**
 * Parses expression.
 */
Expr *Parser::expr() {
  // Begin at the rule with lowest precedence.
  // This will change as more rules are added.
  try {
    return _or();
  }
  catch (ParserException &e) {
    std::cout << e.what() << std::endl;
    hadError = true;
  }
  return nullptr;
}

/**
 * Parses logical 'or' expression.
 */
Expr *Parser::_or() {
  Expr *expr = _and();

  while (match(TOKEN_OR)) {
    Token _operator = previous();
    Expr *right = _and();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }

  return expr;
}

/**
 * Parses logical 'and' expression.
 */
Expr *Parser::_and() {
  Expr *expr = equality();

  while (match(TOKEN_AND)) {
    Token _operator = previous();
    Expr *right = equality();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }

  return expr;
}

/**
 * Parses equality expression.
 */
Expr *Parser::equality() {
  Expr *expr = comparison();

  while (match(TOKEN_BANG_EQUAL) || match(TOKEN_EQUAL_EQUAL)) {
    Token _operator = previous();
    Expr *right = comparison();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }
  
  return expr;
}

/**
 * Parses comparison expression.
 */
Expr *Parser::comparison() {
  Expr *expr = addition();

  while (match(TOKEN_LESS_EQUAL) || match(TOKEN_GREATER_EQUAL) ||
         match(TOKEN_LESS) || match(TOKEN_GREATER)) {
    Token _operator = previous();
    Expr *right = addition();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }

  return expr;
}

/**
 * Parses addition expression.
 */
Expr *Parser::addition() {
  Expr *expr = multiplication();

  while (match(TOKEN_PLUS) || match(TOKEN_MINUS)) {
    Token _operator = previous();
    Expr *right = multiplication();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }

  return expr;
}

/**
 * Parses multiplication expression.
 */
Expr *Parser::multiplication() {
  Expr *expr = unary();

  while (match(TOKEN_STAR) || match(TOKEN_SLASH)) {
    Token _operator = previous();
    Expr *right = unary();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }

  return expr;
}

/**
 * Parses unary expression.
 */
Expr *Parser::unary() {
  if (match(TOKEN_MINUS) || match(TOKEN_BANG) || match(TOKEN_NOT)) {
    Token _operator = previous();
    Expr *right = unary();
    Expr *expr = new UnaryExpr(_operator, right);
    return expr;
  }

  return primary();
}

/**
 * Parses primary expression.
 */
Expr* Parser::primary() {
  // Boolean literals
  if (match(TOKEN_TRUE) || match(TOKEN_FALSE)) {
    return new Boolean(previous());
  }

  // Keywords that are constants
  // e.g. "pi", "euler", etc.
  if (match(TOKEN_PI) || match(TOKEN_EULER)) {
    return new KeywordConstant(previous());
  }

  // Keywords that act an unary operators
  // e.g. "output", "mag"
  if (match(TOKEN_J) || match(TOKEN_OUTPUT) || match(TOKEN_INPUT) ||
      match(TOKEN_MAG) || match(TOKEN_RE) || match(TOKEN_IM) ||
      match(TOKEN_ANGLEOF)) {
    Token _operator = previous();
    // TODO: should this be unary or primary?
    Expr *right = unary();
    return new UnaryExpr(_operator, right);
  }

  // Real number literals
  if (match(TOKEN_NUMBER_LITERAL)) {
    return new RealNumber(previous());
  }
  // Imaginary number literals
  if (match(TOKEN_IM_NUMBER_LITERAL)) {
    return new ImaginaryNumber(previous());
  }

  // String literals
  if (match(TOKEN_STRING_LITERAL)) {
    return new String(previous());
  }

  // Parenthesized groupings
  if (match(TOKEN_LEFT_PAREN)) {
    Expr *_expr = expr();

    if (peek().getTokenType() == TOKEN_J) {
      throw ParserException("unexpected 'j'. Did you mean to prefix it?");
    }

    if (!match(TOKEN_RIGHT_PAREN)) {
      throw ParserException("expected ')' after expression.");
    }

    return new Grouping(_expr);
  }

  throw ImplementationException("unhandled TokenType while parsing primary.");
  return nullptr;
}

/**
 * Returns true and advances if the next token has matching TokenType.
 */
bool Parser::match(TokenType type) {
  if (check(type)) {
    advance();
    return true;
  }
  return false;
}

/**
 * Returns true if next token has matching TokenType.
 */
bool Parser::check(TokenType type) {
  if (isAtEnd()) {
    return false;
  }
  return peek().getTokenType() == type;
}

/**
 * Returns next token and increments current index.
 */
Token Parser::advance() {
  if (!isAtEnd()) {
    current++;
  }
  return previous();
}

/**
 * Returns true if EOF token has been reached.
 */
bool Parser::isAtEnd() {
  return peek().getTokenType() == TOKEN_EOF;
}

/**
 * Returns next token without incrementing current index.
 */
Token Parser::peek() {
  return tokens[current];
}

/**
 * Returns previous token.
 */
Token Parser::previous() {
  return tokens[current - 1];
}

} // namespace napkin
