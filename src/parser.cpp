#include "parser.h"

namespace napkin {

/**
 * Constructs AST and returns a list of statements.
 */
std::vector<Stmt *> Parser::parse() {
  std::vector<Stmt *> stmts;
  while (!isAtEnd()) {
    ignoreNewlines(); // Ignore empty lines
    // Handle an empty line at the end of the file
    if (tokens[current].getTokenType() == TOKEN_EOF) break;
    stmts.push_back(stmt());
  }
  return stmts;
}

/**
 * Parses a statement.
 */
Stmt *Parser::stmt() {
  // Will add more types of statements later
  if (match(TOKEN_OUTPUT)) {
    return outputStmt();
  }
  if (match(TOKEN_LEFT_BRACE)) {
    return new BlockStmt(blockStmt());
  }
  if (match(TOKEN_IF)) {
    return ifStmt();
  }
  if (match(TOKEN_WHILE)) {
    return whileStmt();
  }
  // Otherwise it is an expression statement
  return exprStmt();
}

/**
 * Parses expression statement.
 */
Stmt *Parser::exprStmt() {
  Expr *value = expr();
  checkTerminator();
  return new ExprStmt(value);
}

/**
 * Parses "output" statement.
 */
Stmt *Parser::outputStmt() {
  Expr *value = expr();
  checkTerminator();
  return new OutputStmt(value);
}

/**
 * Parses a block statment.
 */
std::vector<Stmt *> Parser::blockStmt() {
  std::vector<Stmt *> stmts;

  // Continue gathering statements to be added to the block until we reach '}'
  // or end of file
  while (!check(TOKEN_RIGHT_BRACE) && !isAtEnd()) {
    ignoreNewlines();
    stmts.push_back(stmt());
  }

  if (!match(TOKEN_RIGHT_BRACE)) {
    throw ParserException("expected '}' after block.");
  }

  return stmts;
}

/**
 * Parses if statement.
 */
Stmt *Parser::ifStmt() {
  Expr *condition = expr();
  ignoreNewlines();

  Stmt *thenBranch = stmt();
  Stmt *elseBranch = nullptr;
  ignoreNewlines();
  if (match(TOKEN_ELSE)) {
    ignoreNewlines();
    elseBranch = stmt();
  }

  return new IfStmt(condition, thenBranch, elseBranch);
}

/**
 * Parses while statement.
 */
Stmt *Parser::whileStmt() {
  Expr *condition = expr();
  ignoreNewlines();

  Stmt *body = stmt();

  return new WhileStmt(condition, body);
}

/**
 * Parses expression.
 */
Expr *Parser::expr() {
  // Begin at the rule with lowest precedence.
  // This will change as more rules are added.
  try {
    if (match(TOKEN_ARROW)) {
      return lambdaExpr();
    } else {
      return assignExpr();
    }
  }
  catch (ParserException &e) {
    std::cout << e.what() << std::endl;
    hadError = true;
  }
  return nullptr;
}

/**
 * Parses lambda expression
 */
Expr *Parser::lambdaExpr() {
  std::vector<Identifier *> parameters;
  // Parse parameter list
  // note: list may be empty brackets
  if (match(TOKEN_LEFT_PAREN)) {
    if (check(TOKEN_IDENTIFIER)) {
      parameters.push_back(new Identifier(advance()));
      while (match(TOKEN_COMMA)) {
        if (check(TOKEN_IDENTIFIER)) {
          parameters.push_back(new Identifier(advance()));
        } else {
          throw napkin::ParserException(
              "expected identifier after comma in parameter list.");
        }
      }
    }
    if (!match(TOKEN_RIGHT_PAREN)) {
      throw napkin::ParserException(
          "expected closing ')' after parameter list.");
    }
  }

  if (!match(TOKEN_LEFT_BRACE)) {
    throw napkin::ParserException("expected opening '{' for lambda body.");
  }
  BlockStmt *body = new BlockStmt(blockStmt());
  return new LambdaExpr(parameters, body);
}

/**
 * Parses assignment and explicit variable declaration expressions.
 */
Expr *Parser::assignExpr() {
  TokenType next = peek(1).getTokenType();
  TokenType nextNext = peek(2).getTokenType();
  if (next == TOKEN_IDENTIFIER &&
      (nextNext == TOKEN_EQUAL || nextNext == TOKEN_COLON_EQUAL)) {
    Token name = advance();
    // Consume '=' or ':=' token
    advance();
    if (nextNext == TOKEN_EQUAL) {
      Expr *value = expr();
      return new AssignExpr(name, value);
    } else if (nextNext == TOKEN_COLON_EQUAL) {
      Expr *value = expr();
      return new VarDeclExpr(name, value);
    } else {
      throw napkin::ImplementationException("unhandled assignment operator");
    }
  } else {
    return _or();
  }
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
  Expr *expr = exponentiation();

  while (match(TOKEN_STAR) || match(TOKEN_SLASH)) {
    Token _operator = previous();
    Expr *right = exponentiation();
    // Attach the old expr to the left and the new one to the right
    expr = new BinaryExpr(_operator, expr, right);
  }

  return expr;
}

/**
 * Parses exponentiation expression.
 */
Expr *Parser::exponentiation() {
  Expr *expr = unary();

  while (match(TOKEN_STAR_STAR)) {
    Token _operator = previous();
    Expr *right = exponentiation();
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

  return call();
}

/**
 * Parses function call.
 */
Expr *Parser::call() {
  // Parse LHS of function call
  Expr *expr = primary();

  // Allows chaining function calls (if one function returns another function)
  while (true) {
    if (match(TOKEN_LEFT_PAREN)) {
      expr = finishCall(expr);
    } else {
      break;
    }
  }
  return expr;
}

/**
 * Helper to add argument list to a function call.
 * @param callee The LHS of a function call
 */
Expr *Parser::finishCall(Expr *callee) {
  std::vector<Expr *> arguments;
  if (!check(TOKEN_RIGHT_PAREN)) {
    do {
      arguments.push_back(expr());
    } while (match(TOKEN_COMMA));
  }

  if (check(TOKEN_RIGHT_PAREN)) {
    Token paren = advance();
    return new CallExpr(callee, paren, arguments);
  } else {
    throw RuntimeException("expected ')' after arguments in function call.");
  }
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
  // e.g. "mag", "re"
  if (match(TOKEN_J) || match(TOKEN_MAG) || match(TOKEN_RE) ||
      match(TOKEN_IM) || match(TOKEN_ANGLEOF)) {
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

  // Identifiers
  if (match(TOKEN_IDENTIFIER)) {
    return new Identifier(previous());
  }

  throw ImplementationException("unhandled TokenType: " +
                                peek().tokenTypeAsString() +
                                " while parsing primary.");
  return nullptr;
}

/**
 * Ignores (consumes) a group of consecutive newlines.
 * Can be used to ignore empty lines.
 */
void Parser::ignoreNewlines() {
  while (match(TOKEN_NEWLINE)) {};
}

/**
 * Checks for valid token to terminate a statment.
 * If no valid terminator, throws ParserException
 * Will consume a newline. Does not consume a closing '}'
 */
void Parser::checkTerminator() {
  if (!match(TOKEN_NEWLINE) && !(peek().getTokenType() == (TOKEN_RIGHT_BRACE))) {
    throw ParserException("expected newline or ';' after expression.");
  }
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
  return tokens[current].getTokenType() == TOKEN_EOF;
}

/**
 * Returns next token without incrementing current index.
 */
Token Parser::peek() {
  return tokens[current];
}

/**
 * Returns token 'n' places ahead without incrementing current index.
 */
Token Parser::peek(unsigned int n) {
  return tokens[current + n - 1];
}

/**
 * Returns previous token.
 */
Token Parser::previous() {
  return tokens[current - 1];
}

} // namespace napkin
