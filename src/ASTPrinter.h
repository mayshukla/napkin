#ifndef NAPKIN_ASTPRINTER_H_
#define NAPKIN_ASTPRINTER_H_

#include "ASTVisitor.h"
#include "AST.h"

namespace napkin {

/**
 * Class to print AST in a lisp-like Polish notation for debugging purposes
 */
class ASTPrinter : public ASTVisitor<std::string> {
public:
  virtual std::string visitStmt(Stmt *stmt);
  virtual std::string visitExprStmt(ExprStmt *stmt);
  virtual std::string visitOutputStmt(OutputStmt *stmt);
  virtual std::string visitExpr(Expr *expr);
  virtual std::string visitBinaryExpr(BinaryExpr *expr);
  virtual std::string visitGrouping(Grouping *expr);
  virtual std::string visitUnaryExpr(UnaryExpr *expr);
  virtual std::string visitIdentifier(Identifier *expr);
  virtual std::string visitRealNumber(RealNumber *expr);
  virtual std::string visitImaginaryNumber(ImaginaryNumber *expr);
  virtual std::string visitString(String *expr);
  virtual std::string visitBoolean(Boolean *expr);
  virtual std::string visitKeywordConstant(KeywordConstant *expr);
};

} // namespace napkin

#endif
