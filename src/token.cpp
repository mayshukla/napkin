#include "token.h"

namespace napkin {

/**
 * Converts a TokenType to a printable string
 */
std::string tokenTypeAsString(TokenType tokenType) {
  switch (tokenType) {

  // Single character
  case TOKEN_LEFT_PAREN:
    return "TOKEN_LEFT_PAREN";
    break;
  case TOKEN_RIGHT_PAREN:
    return "TOKEN_RIGHT_PAREN";
    break;
  case TOKEN_LEFT_BRACE:
    return "TOKEN_LEFT_BRACE";
    break;
  case TOKEN_RIGHT_BRACE:
    return "TOKEN_RIGHT_BRACE";
    break;
  case TOKEN_LEFT_BRACKET:
    return "TOKEN_LEFT_BRACKET";
    break;
  case TOKEN_RIGHT_BRACKET:
    return "TOKEN_RIGHT_BRACKET";
    break;
  case TOKEN_DOT:
    return "TOKEN_DOT";
    break;
  case TOKEN_COMMA:
    return "TOKEN_COMMA";
    break;

  case TOKEN_EQUAL:
    return "TOKEN_EQUAL";
    break;
  case TOKEN_BANG:
    return "TOKEN_BANG";
    break;
  case TOKEN_LESS:
    return "TOKEN_LESS";
    break;
  case TOKEN_GREATER:
    return "TOKEN_GREATER";
    break;
  case TOKEN_PLUS:
    return "TOKEN_PLUS";
    break;
  case TOKEN_MINUS:
    return "TOKEN_MINUS";
    break;
  case TOKEN_STAR:
    return "TOKEN_STAR";
    break;
  case TOKEN_SLASH:
    return "TOKEN_SLASH";
    break;
  case TOKEN_NEWLINE:
    return "TOKEN_NEWLINE";
    break;

  case TOKEN_J:
    return "TOKEN_J";
    break;

  // Few characters
  case TOKEN_EQUAL_EQUAL:
    return "TOKEN_EQUAL_EQUAL";
    break;
  case TOKEN_BANG_EQUAL:
    return "TOKEN_BANG_EQUAL";
    break;
  case TOKEN_LESS_EQUAL:
    return "TOKEN_LESS_EQUAL";
    break;
  case TOKEN_GREATER_EQUAL:
    return "TOKEN_GREATER_EQUAL";
    break;
  case TOKEN_STAR_STAR:
    return "TOKEN_STAR_STAR";
    break;

  // Identifiers and literals
  case TOKEN_IDENTIFIER:
    return "TOKEN_IDENTIFIER";
    break;
  case TOKEN_NUMBER_LITERAL:
    return "TOKEN_NUMBER_LITERAL";
    break;
  case TOKEN_IM_NUMBER_LITERAL:
    return "TOKEN_IM_NUMBER_LITERAL";
  case TOKEN_STRING_LITERAL:
    return "TOKEN_STRING_LITERAL";
    break;

    
  // Keywords
  case TOKEN_FUN:
    return "TOKEN_FUN";
    break;
  case TOKEN_IF:
    return "TOKEN_IF";
    break;
  case TOKEN_ELSE:
    return "TOKEN_ELSE";
    break;
  case TOKEN_ELIF:
    return "TOKEN_ELIF";
    break;
  case TOKEN_FOR:
    return "TOKEN_FOR";
    break;
  case TOKEN_WHILE:
    return "TOKEN_WHILE";
    break;
  case TOKEN_TRUE:
    return "TOKEN_TRUE";
    break;
  case TOKEN_FALSE:
    return "TOKEN_FALSE";
    break;
  case TOKEN_NOT:
    return "TOKEN_NOT";
    break;
  case TOKEN_AND:
    return "TOKEN_AND";
    break;
  case TOKEN_OR:
    return "TOKEN_OR";
    break;
  case TOKEN_OUTPUT:
    return "TOKEN_OUTPUT";
    break;
  case TOKEN_RETURN:
    return "TOKEN_RETURN";
    break;
  case TOKEN_INPUT:
    return "TOKEN_INPUT";
    break;
  case TOKEN_POLAR:
    return "TOKEN_POLAR";
    break;
  case TOKEN_RE:
    return "TOKEN_RE";
    break;
  case TOKEN_IM:
    return "TOKEN_IM";
    break;
  case TOKEN_ANGLEOF:
    return "TOKEN_ANGLEOF";
    break;
  case TOKEN_MAG:
    return "TOKEN_MAG";
    break;
  case TOKEN_PI:
    return "TOKEN_PI";
    break;
  case TOKEN_EULER:
    return "TOKEN_EULER";
    break;

  case TOKEN_EOF:
    return "TOKEN_EOF";
    break;
  }
}

unsigned int Token::getLine() {
  return this->line;
}

unsigned int Token::getColumn() {
  return this->column;
}

TokenType Token::getTokenType() {
  return this->tokenType;
}

std::string Token::tokenTypeAsString() {
  return napkin::tokenTypeAsString(this->tokenType);
}

std::string Token::getLexeme() {
  return lexeme;
}

} // namespace napkin
