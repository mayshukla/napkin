#include "interpreter.h"

namespace napkin {

NObject *Interpreter::visitExpr(Expr *expr) {
  return expr->accept(this);
}

NObject *Interpreter::visitBinaryExpr(BinaryExpr* expr) {
  TokenType _operator = expr->_operator.getTokenType();
  NObject *left = expr->left->accept(this);
  NObject  *right = expr->right->accept(this);

  switch (_operator) {
  case TOKEN_PLUS:
    // TODO: catch RuntimeException
    return nAdd(left, right);
    break;
  case TOKEN_MINUS:
    break;
  case TOKEN_STAR:
    break;
  case TOKEN_SLASH:
    break;
  case TOKEN_EQUAL_EQUAL:
    break;
  case TOKEN_BANG_EQUAL:
    break;
  case TOKEN_LESS_EQUAL:
    break;
  case TOKEN_GREATER_EQUAL:
    break;
  case TOKEN_LESS:
    break;
  case TOKEN_GREATER:
    break;
  default:
    // should be unreachable if parser is set up correctly
    throw "Error: not a binary operator.";
    return nullptr;
    break;
  }

  // Unreachable
  return nullptr;
}

NObject *Interpreter::visitGrouping(Grouping *expr) {
  return nullptr;
}

NObject *Interpreter::visitUnaryExpr(UnaryExpr *expr) {
  return nullptr;
}

NObject *Interpreter::visitIdentifier(Identifier *expr) {
  return nullptr;
}

NObject *Interpreter::visitRealNumber(RealNumber *expr) {
  return new NRealNumber(expr->value);
}

NObject *Interpreter::visitImaginaryNumber(ImaginaryNumber *expr) {
  return nullptr;
}

NObject *Interpreter::visitString(String *expr) {
  return nullptr;
}

NObject *Interpreter::visitBoolean(Boolean *expr) {
  return nullptr;
}

NObject *Interpreter::visitKeywordConstant(KeywordConstant *expr) {
  return nullptr;
}

} // namespace napkin
