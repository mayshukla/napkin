#include "ASTPrinter.h"

namespace napkin {

std::string ASTPrinter::visitBinaryExpr(BinaryExpr* expr) {
  std::string _operator = expr->_operator.getLexeme();
  std::string left = expr->left->accept(this);
  std::string right = expr->right->accept(this);
  return "(" + _operator + " " + left + " " + right + ")";
}

std::string ASTPrinter::visitGrouping(Grouping *expr) {
  std::string contents = expr->contents->accept(this);
  return std::string("(Grouping ") + contents + ")";
}

std::string ASTPrinter::visitUnaryExpr(UnaryExpr *expr) {
  std::string _operator = expr->_operator.getLexeme();
  std::string operand = expr->operand->accept(this);
  return "(" + _operator + " " + operand + ")";
}

std::string ASTPrinter::visitIdentifier(Identifier *expr) {
  return expr->token.getLexeme();
}

std::string ASTPrinter::visitRealNumber(RealNumber *expr) {
  return std::to_string(expr->value); // convert double to string
}

std::string ASTPrinter::visitImaginaryNumber(ImaginaryNumber *expr) {
  std::string value = std::to_string(expr->value);
  return "j" + value;
}

std::string ASTPrinter::visitString(String *expr) {
  return expr->token.getLexeme();
}

} // namespace napkin
