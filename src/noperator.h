#ifndef NAPKIN_NOPERATOR_H_
#define NAPKIN_NOPERATOR_H_

#include <cmath>

#include "nobject.h"
#include "nexception.h"

/**
 * Defines napkin language operators on NObjects
 */

namespace napkin {

// Operators
NObject *nAdd(NObject *left, NObject* right);
NObject *nSubtract(NObject *left, NObject* right);
NObject *nNegate(NObject *right);
NObject *nMultiply(NObject *left, NObject *right);
NObject *nJ(NObject *right);
NObject *nDivide(NObject *left, NObject *right);
NObject *nNot(NObject *right);
NObject *nLogicalOr(NObject *left, NObject *right);
NObject *nLogicalAnd(NObject *left, NObject *right);
NObject *nLogicalEqual(NObject *left, NObject *right);
NObject *nLogicalNotEqual(NObject *left, NObject *right);

// Helpers
bool isTruthy(NObject *object);

} // namespace napkin

#endif
