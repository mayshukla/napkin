#ifndef NAPKIN_AST_H_
#define NAPKIN_AST_H_

#include <string> // std::stod()

#include "token.h"
#include "ASTVisitor.h"
#include "nobject.h"

/**
 * Abstract Syntax Tree Classes
 */

namespace napkin {

/**
 * Base class for statements.
 * TODO
 */
class Stmt {
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
 * Paranthesized groups.
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
  UnaryExpr(Token t_operator, Expr *t_operand)
      : _operator(t_operator), operand(t_operand){};
  virtual std::string accept(ASTVisitor<std::string> *visitor) {
    return visitor->visitUnaryExpr(this);
  }
  virtual NObject *accept(ASTVisitor<NObject *> *visitor) {
    return visitor->visitUnaryExpr(this);
  }

  Token _operator;
  Expr *operand;
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
