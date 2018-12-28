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
    return nSubtract(left, right);
    break;
  case TOKEN_STAR:
    return nMultiply(left, right);
    break;
  case TOKEN_SLASH:
    return nDivide(left, right);
    break;
  case TOKEN_EQUAL_EQUAL:
    return nLogicalEqual(left, right);
    break;
  case TOKEN_BANG_EQUAL:
    return nLogicalNotEqual(left, right);
    break;
  case TOKEN_OR:
    return nLogicalOr(left, right);
    break;
  case TOKEN_AND:
    return nLogicalAnd(left, right);
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
    throw RuntimeException("Error: not a binary operator.");
    return nullptr;
    break;
  }

  // Unreachable
  return nullptr;
}

NObject *Interpreter::visitGrouping(Grouping *expr) {
  return expr->contents->accept(this);
}

NObject *Interpreter::visitUnaryExpr(UnaryExpr *expr) {
  TokenType _operator = expr->_operator.getTokenType();
  NObject  *right = expr->right->accept(this);

  // TODO: implement all unary operators
  switch (_operator) {
  case TOKEN_MINUS:
    return nNegate(right);
    break;
  case TOKEN_J:
    // 'j' may be used as an operator meaning "multiply by j1"
    return nJ(right);
    break;
  case TOKEN_BANG:
    return nNot(right);
  case TOKEN_NOT:
    return nNot(right);
  default:
    // should be unreachable if parser is set up correctly
    throw RuntimeException("Error: not a unary operator.");
    return nullptr;
    break;
  }

  // Unreachable
  return nullptr;
}

NObject *Interpreter::visitIdentifier(Identifier *expr) {
  return nullptr;
}

NObject *Interpreter::visitRealNumber(RealNumber *expr) {
  return new NRealNumber(expr->value);
}

NObject *Interpreter::visitImaginaryNumber(ImaginaryNumber *expr) {
  return new NComplexNumber(0, expr->value);
}

NObject *Interpreter::visitString(String *expr) {
  return new NString(expr->token.getLexeme());
}

NObject *Interpreter::visitBoolean(Boolean *expr) {
  if (expr->token.getTokenType() == TOKEN_TRUE) {
    return new NBoolean(true);
  }
  return new NBoolean(false);
}

NObject *Interpreter::visitKeywordConstant(KeywordConstant *expr) {
  return nullptr;
}

} // namespace napkin
