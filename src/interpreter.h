#ifndef NAPKIN_INTERPRETER_H_
#define NAPKIN_INTERPRETER_H_

#include "ASTVisitor.h"
#include "AST.h"
#include "nobject.h"
#include "noperator.h"
#include "RuntimeException.h"

namespace napkin {

/**
 * Tree-walk interpreter.
 */
class Interpreter : public ASTVisitor<NObject *> {
public:
  virtual NObject *visitExpr(Expr *expr);
  virtual NObject *visitBinaryExpr(BinaryExpr *expr);
  virtual NObject *visitGrouping(Grouping *expr);
  virtual NObject *visitUnaryExpr(UnaryExpr *expr);
  virtual NObject *visitIdentifier(Identifier *expr);
  virtual NObject *visitRealNumber(RealNumber *expr);
  virtual NObject *visitImaginaryNumber(ImaginaryNumber *expr);
  virtual NObject *visitString(String *expr);
  virtual NObject *visitBoolean(Boolean *expr);
  virtual NObject *visitKeywordConstant(KeywordConstant *expr);
};

} // namespace napkin

#endif
