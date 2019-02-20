#include "nclosure.h"

namespace napkin {

NClosure::NClosure(LambdaExpr *t_expr, const Environment *t_environment) {
  expr = t_expr;
  // Create a new environment and copy over the environment passed in the
  // contructor
  environment = new Environment;
  *environment = *t_environment;
}

/**
 * Executes the function.
 * TODO
 */
NObject *NClosure::call(Interpreter *interpreter,
                        std::vector<NObject *> arguments) {
  return nullptr;
}

int NClosure::arity() {
  return expr->parameters.size();
}

}
