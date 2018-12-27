#include "noperator.h"

// TODO: refactor type checks

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
  if (left->getType() == N_REAL_NUMBER &&
      right->getType() == N_COMPLEX_NUMBER) {
    double left_value = ((NRealNumber *)left)->value;
    double right_re = ((NComplexNumber *)right)->re;
    double right_im = ((NComplexNumber *)right)->im;

    double result_re = left_value + right_re;
    double result_im = right_im;

    return new NComplexNumber(result_re, result_im);
  }

  // Left complex, right real
  if (left->getType() == N_COMPLEX_NUMBER &&
      right->getType() == N_REAL_NUMBER) {
    double left_re = ((NComplexNumber *)left)->re;
    double left_im = ((NComplexNumber *)left)->im;
    double right_value = ((NRealNumber *)right)->value;

    double result_re = left_re + right_value;
    double result_im = left_im;

    return new NComplexNumber(result_re, result_im);
  }

  // Both complex
  if (left->getType() == N_COMPLEX_NUMBER &&
      right->getType() == N_COMPLEX_NUMBER) {
    double left_re = ((NComplexNumber *)left)->re;
    double left_im = ((NComplexNumber *)left)->im;
    double right_re = ((NComplexNumber *)right)->re;
    double right_im = ((NComplexNumber *)right)->im;

    double result_re = left_re + right_re;
    double result_im = left_im + right_im;

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

/**
 * Multiplies two napkin numbers (complex or real).
 * Will cast up to complex.
 */
NObject *nMultiply(NObject *left, NObject *right) {
  // Not a number
  if ((left->getType() != N_REAL_NUMBER &&
       left->getType() != N_COMPLEX_NUMBER) ||
      (right->getType() != N_REAL_NUMBER &&
       right->getType() != N_COMPLEX_NUMBER)) {
    RuntimeException ex("Invalid operands for multiplication/division.");
    throw ex;
  }

  // Both real numbers
  if (left->getType() == N_REAL_NUMBER && right->getType() == N_REAL_NUMBER) {
    double result =
        ((NRealNumber *)left)->value * ((NRealNumber *)right)->value;
    return new NRealNumber(result);
  }

  // Left real, right complex
  if (left->getType() == N_REAL_NUMBER &&
      right->getType() == N_COMPLEX_NUMBER) {
    double left_value = ((NRealNumber *)left)->value;
    double right_re = ((NComplexNumber *)right)->re;
    double right_im = ((NComplexNumber *)right)->im;

    double result_re = left_value * right_re;
    double result_im = left_value * right_im;

    return new NComplexNumber(result_re, result_im);
  }

  // Left complex, right real
  if (left->getType() == N_COMPLEX_NUMBER &&
      right->getType() == N_REAL_NUMBER) {
    double left_re = ((NComplexNumber *)left)->re;
    double left_im = ((NComplexNumber *)left)->im;
    double right_value = ((NRealNumber *)right)->value;

    double result_re = left_re * right_value;
    double result_im = left_im * right_value;

    return new NComplexNumber(result_re, result_im);
  }

  // Both complex
  if (left->getType() == N_COMPLEX_NUMBER &&
      right->getType() == N_COMPLEX_NUMBER) {
    double left_re = ((NComplexNumber *)left)->re;
    double left_im = ((NComplexNumber *)left)->im;
    double right_re = ((NComplexNumber *)right)->re;
    double right_im = ((NComplexNumber *)right)->im;

    double result_re = left_re * right_re - left_im * right_im;
    double result_im = left_re * right_im + left_im * right_re;

    return new NComplexNumber(result_re, result_im);
  }

  // Unreachable
  return nullptr;
}

/**
 * Multiplies a number by 'j1'
 */
NObject *nJ(NObject *right) {
  // Not a number
  if (right->getType() != N_REAL_NUMBER &&
      right->getType() != N_COMPLEX_NUMBER) {
    RuntimeException ex("Invalid operand for unary negation.");
    throw ex;
  }
  NComplexNumber multiplier(0, 1);
  return nMultiply(&multiplier, right);
}


/**
 * Divides two napkin numbers (complex or real).
 * Will cast up to complex.
 */
NObject *nDivide(NObject *left, NObject *right) {
  // Not a number
  if ((left->getType() != N_REAL_NUMBER &&
       left->getType() != N_COMPLEX_NUMBER) ||
      (right->getType() != N_REAL_NUMBER &&
       right->getType() != N_COMPLEX_NUMBER)) {
    RuntimeException ex("Invalid operands for multiplication/division.");
    throw ex;
  }

  // Both real numbers
  if (left->getType() == N_REAL_NUMBER && right->getType() == N_REAL_NUMBER) {
    double result =
        ((NRealNumber *)left)->value / ((NRealNumber *)right)->value;
    return new NRealNumber(result);
  }

  // Left complex, right real
  if (left->getType() == N_COMPLEX_NUMBER &&
      right->getType() == N_REAL_NUMBER) {
    double left_re = ((NComplexNumber *)left)->re;
    double left_im = ((NComplexNumber *)left)->im;
    double right_value = ((NRealNumber *)right)->value;

    double result_re = left_re / right_value;
    double result_im = left_im / right_value;

    return new NComplexNumber(result_re, result_im);
  }

  // Left real, right complex
  if (left->getType() == N_REAL_NUMBER &&
      right->getType() == N_COMPLEX_NUMBER) {
    // Cast left to a complex number and perform the division
    NComplexNumber temp_left(((NRealNumber *)left)->value, 0);
    return nDivide(&temp_left, right);
  }

  // Both complex
  if (left->getType() == N_COMPLEX_NUMBER &&
      right->getType() == N_COMPLEX_NUMBER) {
    double left_re = ((NComplexNumber *)left)->re;
    double left_im = ((NComplexNumber *)left)->im;
    double right_re = ((NComplexNumber *)right)->re;
    double right_im = ((NComplexNumber *)right)->im;

    double result_re = left_re * right_re + left_im * right_im;
    double result_im = -(left_re * right_im) + (right_re * left_im);

    double divisor = pow(right_re, 2) + pow(right_im, 2);
    result_re = result_re / divisor;
    result_im = result_im / divisor;

    return new NComplexNumber(result_re, result_im);
  }

  // Unreachable
  return nullptr;
}

} // namespace napkin
