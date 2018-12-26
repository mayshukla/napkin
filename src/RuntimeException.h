#ifndef NAPKIN_RUNTIME_EXCEPTION_H_
#define NAPKIN_RUNTIME_EXCEPTION_H_

#include <exception>

namespace napkin {

class RuntimeException : public std::exception {
private:
  virtual const char* what() const throw() {
    return "napkin runtime error occured";
  }
};

} // namespace napkin

#endif
