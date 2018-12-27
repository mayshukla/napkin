#include "noperator.h"

namespace napkin {

/**
 * Adds two napkin numbers (complex or real).
 * Will cast up to complex.
 */
NObject *nAdd(NObject *left, NObject* right) {
  // Not a number
  if ((left->getType() != N_REAL_NUMBER &&
       left->getType() != N_COMPLEX_NUMBER) ||
      (right->getType() != N_REAL_NUMBER &&
       right->getType() != N_COMPLEX_NUMBER)) {
    RuntimeException ex("Invalid operands for addition/subtraction.");
    throw ex;
  }

  // Both real numbers
  if (left->getType() == N_REAL_NUMBER && right->getType() == N_REAL_NUMBER) {
    double result =
        ((NRealNumber *)left)->value + ((NRealNumber *)right)->value;
    return new NRealNumber(result);
  }

  // Left real, right complex
  if (left->getType() == N_REAL_NUMBER && right->getType() == N_COMPLEX_NUMBER) {
    double result_re =
        ((NRealNumber *)left)->value + ((NComplexNumber *)right)->re;
    double result_im = ((NComplexNumber *)right)->im;
    return new NComplexNumber(result_re, result_im);
  }

  // Left complex, right real
  if (left->getType() == N_COMPLEX_NUMBER && right->getType() == N_REAL_NUMBER) {
    double result_re =
        ((NComplexNumber *)left)->re + ((NRealNumber *)right)->value;
    double result_im = ((NComplexNumber *)left)->im;
    return new NComplexNumber(result_re, result_im);
  }

  // Both complex
  if (left->getType() == N_COMPLEX_NUMBER && right->getType() == N_COMPLEX_NUMBER) {
    double result_re =
        ((NComplexNumber *)left)->re + ((NComplexNumber *)right)->re;
    double result_im =
        ((NComplexNumber *)left)->im + ((NComplexNumber *)right)->im;
    return new NComplexNumber(result_re, result_im);
  }

  // Unreachable
  return nullptr;
}

/**
 * Same as nAdd.
 */
NObject *nSubtract(NObject *left, NObject* right) {
  return nAdd(left, nNegate(right));
}

/**
 * Returns the negative of a number.
 * Preserves type (real or complex).
 */
NObject *nNegate(NObject *right) {
  // Not a number
  if (right->getType() != N_REAL_NUMBER &&
      right->getType() != N_COMPLEX_NUMBER) {
    RuntimeException ex("Invalid operand for unary negation.");
    throw ex;
  }

  // Real number
  if (right->getType() == N_REAL_NUMBER) {
    double result = - (((NRealNumber *)right)->value);
    return new NRealNumber(result);
  }

  // Complex number
  if (right->getType() == N_COMPLEX_NUMBER) {
    double result_re = - (((NComplexNumber *)right)->re);
    double result_im = - (((NComplexNumber *)right)->im);
    return new NComplexNumber(result_re, result_im);
  }

  // Unreachable
  return nullptr;
}

} // namespace napkin
