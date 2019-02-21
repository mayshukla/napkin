#include "interpreter.h"

namespace napkin {

Interpreter::Interpreter(bool repl) {
  globals = new Environment;
  // Define default global variables
  globals->bind("millis", new MillisFunction);
  globals->bind("getline", new GetlineFunction);
  globals->bind("exit", new ExitFunction);
  globals->bind("exit_status", new ExitStatusFunction);
  environment = globals;

  this->repl = repl;
}

/**
 * Executes each statement in a vector of statements
 */
void Interpreter::interpret(std::vector<Stmt *> stmts) {
  for (unsigned int i = 0; i < stmts.size(); i++) {
    visitStmt(stmts[i]);
  }
}

/**
 * Executes a statement.
 */
NObject *Interpreter::visitStmt(Stmt *stmt) {
  // Make the statement call its specific visit method
  return stmt->accept(this);
}

/**
 * Executes an expression statement.
 */
NObject *Interpreter::visitExprStmt(ExprStmt *stmt) {
  // If running in repl, print the result
  // Else, just evaluate that expression
  if (repl) {
    NObject *result = stmt->expr->accept(this);
    if (result != nullptr) {
      std::cout << result->repr() << std::endl;
    }
    return result;
  } else {
    return stmt->expr->accept(this);
  }
}

/**
 * Executes an "output" statement.
 */
NObject *Interpreter::visitOutputStmt(OutputStmt *stmt) {
  // Evaluate the statement to the right of "output"
  NObject *result = stmt->expr->accept(this);
  // Output the string representation of result
  std::cout << result->repr() << std::endl;
  return nullptr;
}

/**
 * Visits a block statement.
 * Creates a new empty environment with the current environment as the enclosing
 * environment and passes this new environment to executeBlockStmt
 */
NObject *Interpreter::visitBlockStmt(BlockStmt *stmt) {
  // Constructs a new environment with the current environment as the enclosing
  // environment
  return executeBlockStmt(stmt, new Environment(environment));
}

/**
 * Executes a block statement.
 * @param stmt The block statement to be executed.
 * @param environment The environment under which to execute the contents of the
 *        block statement.
 */
NObject *Interpreter::executeBlockStmt(BlockStmt *stmt,
                                       Environment *innerEnvironment) {
  // Remembers the current environment
  Environment *previous = this->environment;

  // Sets the current environement to the inner environment
  this->environment = innerEnvironment;

  // Executes all statements in the block
  // Captures the value of the last statement
  // TODO: catch exceptions here to ensure the previous environement is restored
  NObject *value;
  for (unsigned int i = 0; i < stmt->stmts.size(); i++) {
    value = visitStmt(stmt->stmts[i]);
  }

  // Restores the previous environment
  this->environment = previous;
  return value;
}

/**
 * Executes if statement.
 */
NObject *Interpreter::visitIfStmt(IfStmt *stmt) {
  // Checks if condition evaluates to true
  if (isTruthy(stmt->condition->accept(this))) {
    return stmt->thenBranch->accept(this); 
  } else if (stmt->elseBranch != nullptr) {
    // If there is an else clause, execute it
    return stmt->elseBranch->accept(this); 
  }
  return nullptr;
}

/**
 * Executes while statement.
 */
NObject *Interpreter::visitWhileStmt(WhileStmt *stmt) {
  // While the condition evaluates to true, execute the body
  while (isTruthy(stmt->condition->accept(this))) {
    stmt->body->accept(this);
  }
  return nullptr;
}

NObject *Interpreter::visitExpr(Expr *expr) {
  // Make the expression call its specific visit method
  return expr->accept(this);
}

/**
 * Creates new NClosure object
 */
NObject *Interpreter::visitLambdaExpr(LambdaExpr *expr) {
  return new NClosure(expr, this->environment);
}

NObject *Interpreter::visitVarDeclExpr(VarDeclExpr *expr) {
  NObject *value = expr->value->accept(this);
  std::string name = expr->name.getLexeme();
  environment->declareVar(name, value);

  // assignment expressions evaluate to the value assigned
  return value;
}

NObject *Interpreter::visitAssignExpr(AssignExpr *expr) {
  NObject *value = expr->value->accept(this);
  std::string name = expr->name.getLexeme();
  environment->bind(name, value);

  // assignment expressions evaluate to the value assigned
  return value;
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
  case TOKEN_STAR_STAR:
    return nPower(left, right);
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
    return nLessEqual(left, right);
    break;
  case TOKEN_GREATER_EQUAL:
    return nGreaterEqual(left, right);
    break;
  case TOKEN_LESS:
    return nLess(left, right);
    break;
  case TOKEN_GREATER:
    return nGreater(left, right);
    break;
  default:
    // should be unreachable if parser is set up correctly
    throw ImplementationException("binary operator not handled in switch.");
    return nullptr;
    break;
  }

  // Unreachable
  throw ImplementationException("End of switch reached.");
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
    throw ImplementationException("unary operator not handled.");
    return nullptr;
    break;
  }

  // Unreachable
  throw ImplementationException("End of switch reached.");
  return nullptr;
}

NObject *Interpreter::visitCallExpr(CallExpr *expr) {
  // Evaluate the callee
  NObject *callee = expr->callee->accept(this);

  // Evaluate each argument in order
  std::vector<NObject *> arguments;
  for (unsigned long i = 0; i < expr->arguments.size(); i++) {
    arguments.push_back(expr->arguments[i]->accept(this));
  }

  if (!(callee->getType() == N_CALLABLE)) {
    throw RuntimeException("object not callable.");
  }
  NCallable *function = (NCallable *)callee;
  if (arguments.size() != (unsigned long)function->arity()) {
    throw RuntimeException("expected " + std::to_string(function->arity()) +
                           " arguments but got " +
                           std::to_string(arguments.size()) + ".");
  }
  // Function call may require interpreter
  return function->call(this, arguments);
}

NObject *Interpreter::visitIdentifier(Identifier *expr) {
  NObject* value = environment->lookup(expr->token.getLexeme());

  if (value == nullptr) {
    throw RuntimeException("undefined variable '" + expr->token.getLexeme() +
                           "'.");
  }

  return value;
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
  TokenType tokenType = expr->token.getTokenType();

  switch (tokenType) {
    case TOKEN_PI:
      return new NRealNumber(pi);
      break;
    case TOKEN_EULER:
      return new NRealNumber(euler);
      break;
    default:
      throw ImplementationException("Keyword constant not handled in interpreter.");
      break;
  }

  // Unreachable
  throw ImplementationException("End of switch reached.");
  return nullptr;
}

} // namespace napkin
