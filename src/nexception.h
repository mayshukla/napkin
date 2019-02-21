#ifndef NAPKIN_NEXCEPTION_H_
#define NAPKIN_NEXCEPTION_H_

#include <exception>
#include <string>

#include "nobject.h"

namespace napkin {

class NException : public std::exception {
public:
  NException(std::string t_message) : message(t_message) {};
  virtual const char* what() const throw() {
    return message.c_str();
  }
protected:
  std::string message;
};

class LexerException: public NException {
public:
  LexerException(std::string t_message) : NException(t_message) {
    std::string message_prefix = "Napkin LexerException: ";
    message = message_prefix + message;
  };
};

class ParserException : public NException {
public:
  ParserException(std::string t_message) : NException(t_message) {
    std::string message_prefix = "Napkin ParserException: ";
    message = message_prefix + message;
  };
};

class RuntimeException : public NException {
public:
  RuntimeException(std::string t_message) : NException(t_message) {
    std::string message_prefix = "Napkin RuntimeException: ";
    message = message_prefix + message;
  };
};

/**
 * Used to jump through C++ call stack to return from a C++ function
 * @param t_value The value (a napkin object) to be returned
 */
class ReturnException : public RuntimeException {
public:
  ReturnException(NObject *t_value)
      : RuntimeException(
            "Napkin ReturnException: returned from outside a function."),
        value(t_value){};

  NObject *value;
};

/**
 * Indicates that there was an error in implementation, not the user's fault
 */
class ImplementationException : public NException {
public:
  ImplementationException(std::string t_message) : NException(t_message) {
    std::string message_prefix = "Napkin ImplementationException: ";
    message = message_prefix + message;
  };
};

} // namespace napkin

#endif
