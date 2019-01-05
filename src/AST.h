#ifndef NAPKIN_AST_H_
#define NAPKIN_AST_H_

#include <string> // std::stod()
#include <vector>

#include "token.h"
#include "ASTVisitor.h"
#include "nobject.h"

/**
 * Abstract Syntax Tree Classes
 */

namespace napkin {

/**
 * Base class for statements.
 */
class Stmt {
public:
  virtual std::string accept(ASTVisitor<std::string> *visitor) = 0;
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) = 0;
};

/**
 * Expression statement
 */

class ExprStmt : public Stmt {
public:
  ExprStmt(Expr *t_expr) : expr(t_expr){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitExprStmt(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitExprStmt(this);
  }

  Expr *expr; // The expression that forms the statment
};

/**
 * Output statement
 */
class OutputStmt : public Stmt {
public:
  OutputStmt(Expr *t_expr) : expr(t_expr){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitOutputStmt(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitOutputStmt(this);
  }

  Expr *expr; // The expression to be output
};

/**
 * Block enclosed by curly braces.
 */
class BlockStmt : public Stmt {
public:
  BlockStmt(std::vector<Stmt *> t_stmts) : stmts(t_stmts){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitBlockStmt(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitBlockStmt(this);
  }

  std::vector<Stmt *> stmts;
};

/**
 * Base class for expressions.
 */
class Expr {
public:
  virtual std::string accept(ASTVisitor<std::string> *visitor) = 0;
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) = 0;
};

/**
 * Assignment expressions.
 */
class AssignExpr : public Expr {
public:
  AssignExpr(Token t_name, Expr *t_value) : name(t_name), value(t_value){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitAssignExpr(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitAssignExpr(this);
  }

  Token name;
  Expr *value;
};

/**
 * Base class for binary expressions.
 */
class BinaryExpr : public Expr {
public:
  BinaryExpr(Token t_operator, Expr *t_left, Expr *t_right)
      : _operator(t_operator), left(t_left), right(t_right){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitBinaryExpr(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitBinaryExpr(this);
  }

  Token _operator;
  Expr *left;
  Expr *right;
};

/**
 * Parenthesized groups.
 */
class Grouping : public Expr {
public:
  Grouping(Expr *t_contents) : contents(t_contents){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitGrouping(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitGrouping(this);
  }

  Expr *contents;
};

/**
 * Base class for unary expressions.
 */
class UnaryExpr : public Expr {
public:
  UnaryExpr(Token t_operator, Expr *t_right)
      : _operator(t_operator), right(t_right){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitUnaryExpr(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitUnaryExpr(this);
  }

  Token _operator;
  Expr *right;
};

/**
 * Identifiers.
 */
class Identifier : public Expr {
public:
  Identifier(Token t_token) : token(t_token){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitIdentifier(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitIdentifier(this);
  }

  Token token;
};

/**
 * Real number literals.
 */
class RealNumber : public Expr {
public:
  RealNumber(Token t_token) : token(t_token) {
    value = std::stod(token.getLexeme());
  };
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitRealNumber(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitRealNumber(this);
  }

  double value;

private:
  Token token;
};

/**
 * Imaginary number literals.
 */
class ImaginaryNumber : public Expr {
public:
  ImaginaryNumber(Token t_token) : token(t_token) {
    value = std::stod(token.getLexeme());
  };
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitImaginaryNumber(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitImaginaryNumber(this);
  }

  double value;

private:
  Token token;
};

/**
 * String literals.
 */
class String : public Expr {
public:
  String(Token t_token) : token(t_token){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitString(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitString(this);
  }

  Token token;
};

/**
 * Boolean literals.
 */
class Boolean : public Expr {
public:
  Boolean(Token t_token) : token(t_token){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitBoolean(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitBoolean(this);
  }

  Token token;
};

/**
 * Keywords that function as constants (e.g. "pi", "euler", etc)
 */
class KeywordConstant : public Expr {
public:
  KeywordConstant(Token t_token) : token(t_token){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitKeywordConstant(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitKeywordConstant(this);
  }

  Token token;
};

} // namespace napkin

#endif
