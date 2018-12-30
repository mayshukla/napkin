#ifndef NAPKIN_ASTVISITOR_H_
#define NAPKIN_ASTVISITOR_H_

#include <string>

namespace napkin {

// Forward declare concrete classes which will be visited
class Stmt;
class ExprStmt;
class OutputStmt;
class Expr;
class BinaryExpr;
class Grouping;
class UnaryExpr;
class Identifier;
class RealNumber;
class ImaginaryNumber;
class String;
class Boolean;
class KeywordConstant;

/**
 * Base class for visitor that visits various AST classes.
 */
template <class T> class ASTVisitor {
public:
  virtual T visitStmt(Stmt *stmt) = 0;
  virtual T visitExprStmt(ExprStmt *stmt) = 0;
  virtual T visitOutputStmt(OutputStmt *stmt) = 0;
  virtual T visitExpr(Expr *expr) = 0;
  virtual T visitBinaryExpr(BinaryExpr *expr) = 0;
  virtual T visitGrouping(Grouping *expr) = 0;
  virtual T visitUnaryExpr(UnaryExpr *expr) = 0;
  virtual T visitIdentifier(Identifier *expr) = 0;
  virtual T visitRealNumber(RealNumber *expr) = 0;
  virtual T visitImaginaryNumber(ImaginaryNumber *expr) = 0;
  virtual T visitString(String *expr) = 0;
  virtual T visitBoolean(Boolean *expr) = 0;
  virtual T visitKeywordConstant(KeywordConstant *expr) = 0;
};

} // namespace napkin

#endif
