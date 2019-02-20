#ifndef NAPKIN_INTERPRETER_H_
#define NAPKIN_INTERPRETER_H_

#include <iostream>
#include <vector>

#include "AST.h"
#include "ASTVisitor.h"
#include "constants.h"
#include "environment.h"
#include "nativefunction.h"
#include "nclosure.h"
#include "nexception.h"
#include "nobject.h"
#include "noperator.h"

namespace napkin {

/**
 * Tree-walk interpreter.
 */
class Interpreter : public ASTVisitor<NObject *> {
public:
  Interpreter();

  void interpret(std::vector<Stmt *> stmts);

  virtual NObject *visitStmt(Stmt *stmt);
  virtual NObject *visitExprStmt(ExprStmt *stmt);
  virtual NObject *visitOutputStmt(OutputStmt *stmt);
  virtual NObject *visitBlockStmt(BlockStmt *stmt);
  virtual NObject *visitIfStmt(IfStmt *stmt);
  virtual NObject *visitWhileStmt(WhileStmt *stmt);
  virtual NObject *visitExpr(Expr *expr);
  virtual NObject *visitLambdaExpr(LambdaExpr *expr);
  virtual NObject *visitVarDeclExpr(VarDeclExpr *expr);
  virtual NObject *visitAssignExpr(AssignExpr *expr);
  virtual NObject *visitBinaryExpr(BinaryExpr *expr);
  virtual NObject *visitGrouping(Grouping *expr);
  virtual NObject *visitUnaryExpr(UnaryExpr *expr);
  virtual NObject *visitCallExpr(CallExpr *expr);
  virtual NObject *visitIdentifier(Identifier *expr);
  virtual NObject *visitRealNumber(RealNumber *expr);
  virtual NObject *visitImaginaryNumber(ImaginaryNumber *expr);
  virtual NObject *visitString(String *expr);
  virtual NObject *visitBoolean(Boolean *expr);
  virtual NObject *visitKeywordConstant(KeywordConstant *expr);

  NObject *executeBlockStmt(BlockStmt *stmt, Environment *environment);

private:
  // Current scope
  Environment *environment;
  Environment *globals;
};

} // namespace napkin

#endif
