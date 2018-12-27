#ifndef NAPKIN_RUNTIME_EXCEPTION_H_
#define NAPKIN_RUNTIME_EXCEPTION_H_

#include <exception>
#include <string>

namespace napkin {

class NException : public std::exception {
public:
  NException(std::string t_message) : message(t_message) {};
protected:
  std::string message;
};

class LexerException: public NException {
public:
  LexerException(std::string t_message) : NException(t_message){};
  virtual const char* what() const throw() {
    std::string message_builder = "Napkin LexerException: " + message;
    return message_builder.c_str();
  }
private:
};

class RuntimeException : public NException {
public:
  RuntimeException(std::string t_message) : NException(t_message){};
  virtual const char* what() const throw() {
    std::string message_builder = "Napkin RuntimeException: " + message;
    return message_builder.c_str();
  }
};

} // namespace napkin

#endif
