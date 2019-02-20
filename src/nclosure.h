#ifndef NAPKIN_NCLOSURE_H_
#define NAPKIN_NCLOSURE_H_

#include "AST.h"
#include "environment.h"
#include "nobject.h"

#include "interpreter.h"

namespace napkin {

class NClosure : public NCallable {
public:
  NClosure(LambdaExpr *t_expr, const Environment *t_environment);
  virtual NObject *call(Interpreter *interpreter,
                        std::vector<NObject *> arguments);
  virtual int arity();
  virtual std::string repr() { return "<closure>"; }

private:
  LambdaExpr *expr; // The actual "contents" of the function 
  Environment *environment; 
};

} // namespace napkin

#endif
