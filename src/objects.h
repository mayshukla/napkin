#ifndef NAPKIN_OBJECTS_H
#define NAPKIN_OBJECTS_H

namespace napkin {

enum NapkinType {
  OBJECT,
  EXPR,
  GROUPING,
  UNARY_EXPR,
  IDENTIFIER,
  REAL_NUMBER,
  COMPLEX_NUMBER,
  STRING,
  FUNCTION_LITERAL,

  // There will be more types
};

} // namespace napkin

#endif
