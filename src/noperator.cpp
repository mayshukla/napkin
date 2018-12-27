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

/**
 * Returns the logical "not" of an expression
 * Casts to nBoolean
 */
NObject *nNot(NObject *right) {
  return new NBoolean(!isTruthy(right));
}

/**
 * Returns true if a napkin object is considered truthy
 */
bool isTruthy(NObject *object) {
  switch (object->getType()) {
  case N_REAL_NUMBER:
    // Only 0 is false
    if (((NRealNumber *)object)->value == 0) {
      return false;
    }
    return true;
    break;

  case N_COMPLEX_NUMBER:
    // Only 0+j0 is false
    if (((NComplexNumber *)object)->re == 0 &&
        ((NComplexNumber *)object)->im == 0) {
      return false;
    }
    return true;
    break;

  case N_BOOLEAN:
    return ((NBoolean *)object)->value;
    break;

  case N_STRING:
    // Empty string is false
    if (((NString *)object)->value.empty()) {
      return false;
    }
    return true;
    break;
  }
}

/**
 * Returns NBoolean with value true if left and right are considered equal
 */
NObject *nLogicalEqual(NObject *left, NObject *right) {
  NType left_type = left->getType();
  NType right_type = right->getType();

  // Either operand is boolean
  if (left_type == N_BOOLEAN || right_type == N_BOOLEAN) {
    bool left_value = isTruthy(left);
    bool right_value = isTruthy(right);
    if (left_value ==  right_value) {
      return new NBoolean(true);
    }
    return new NBoolean(false);
  }
  
  // Unreachable
  return nullptr;
}

/**
 * Same as nLogicalEqual
 */
NObject *nLogicalNotEqual(NObject *left, NObject *right) {
  NObject *temp_result = nLogicalEqual(left, right);
  bool areEqual = ((NBoolean *)temp_result)->value;
  return new NBoolean(!areEqual);
}

} // namespace napkin
