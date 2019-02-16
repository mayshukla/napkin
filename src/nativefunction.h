#ifndef NAPKIN_NATIVEFUNCTION_H_
#define NAPKIN_NATIVEFUNCTION_H_

#include <chrono>
#include <iostream>

#include "nobject.h"

namespace napkin {

/**
 * Functions written in C++.
 */
class NativeFunction : public NCallable {
};

/**
 * Native function to return the current time in milliseconds
 * https://stackoverflow.com/a/19555298
 */
class MillisFunction : public NativeFunction {
public:
  // Define the arity for millis()
  virtual int arity() {
    return 0;
  }
  virtual NObject *call(Interpreter *interpreter,
                        std::vector<NObject *> arguments) {
    double ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count();
    return new NRealNumber(ms);
  }
  virtual std::string repr() { return "<native function millis>"; }
};

/**
 * Gets a line of input as a napkin string
 */
class GetlineFunction : public NativeFunction {
public:
  virtual int arity() {
    return 0;
  }
  virtual NObject *call(Interpreter *interpreter,
                        std::vector<NObject *> arguments) {
    std::string input;
    std::getline(std::cin, input);
    return new NString(input);
  }
  virtual std::string repr() { return "<native function getline>"; }
};

} // namespace napkin

#endif
