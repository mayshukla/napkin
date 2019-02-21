#include "ASTPrinter.h"

namespace napkin {

std::string ASTPrinter::visitStmt(Stmt *stmt) {
  return stmt->accept(this);
}

std::string ASTPrinter::visitExprStmt(ExprStmt *stmt) {
  return "ExprStmt: " + stmt->expr->accept(this) + "\n";
}

std::string ASTPrinter::visitOutputStmt(OutputStmt *stmt) {
  return "OutputStmt: " + stmt->expr->accept(this) + "\n";
}

std::string ASTPrinter::visitBlockStmt(BlockStmt *stmt) {
  std::string contents;
  contents = "{\n";
  for (unsigned int i = 0; i <  stmt->stmts.size(); i++) {
    contents += stmt->stmts[i]->accept(this);
    contents += "\n";
  }
  contents += "}\n";
  return contents;
}

std::string ASTPrinter::visitIfStmt(IfStmt *stmt) {
  std::string toPrint =
      "IfStmt: \n    Then: " + stmt->thenBranch->accept(this) + "\n";
  if (stmt->elseBranch != nullptr) {
    toPrint += "\n    Else: " + stmt->elseBranch->accept(this) + "\n";
  }
  return toPrint;
}

std::string ASTPrinter::visitWhileStmt(WhileStmt *stmt) {
  return "WhileStmt: " + stmt->body->accept(this) + "\n";
}

std::string ASTPrinter::visitReturnStmt(ReturnStmt *stmt) {
  return "ReturnStmt: " + stmt->value->accept(this) + "\n";
}

std::string ASTPrinter::visitExpr(Expr *expr) {
  return expr->accept(this);
}

std::string ASTPrinter::visitLambdaExpr(LambdaExpr *expr) {
  return "LambdaExpr: " + expr->body->accept(this) + "\n";
}

std::string ASTPrinter::visitVarDeclExpr(VarDeclExpr *expr) {
  std::string name = expr->name.getLexeme();
  std::string value = expr->value->accept(this);
  return "(VarDeclExpr " + name + " " + value + ")";
}

std::string ASTPrinter::visitAssignExpr(AssignExpr *expr) {
  std::string name = expr->name.getLexeme();
  std::string value = expr->value->accept(this);
  return "(assign " + name + " " + value + ")";
}

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
  std::string right = expr->right->accept(this);
  return "(" + _operator + " " + right + ")";
}

std::string ASTPrinter::visitCallExpr(CallExpr *expr) {
  std::string result = "(call (";
  result += expr->callee->accept(this);
  result += ") (";
  for (unsigned long i = 0; i < expr->arguments.size(); i++) {
    result += expr->arguments[i]->accept(this);
    if (i != expr->arguments.size() - 1) {
      result += ", ";
    }
  }
  result += "))";
  return result;
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

std::string ASTPrinter::visitBoolean(Boolean *expr) {
  return expr->token.getLexeme();
}

std::string ASTPrinter::visitKeywordConstant(KeywordConstant *expr) {
  return expr->token.getLexeme();
}

} // namespace napkin
