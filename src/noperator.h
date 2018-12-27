#ifndef NAPKIN_NOPERATOR_H_
#define NAPKIN_NOPERATOR_H_

#include "nobject.h"
#include "nexception.h"

/**
 * Defines napkin language operators on NObjects
 */

namespace napkin {

NObject *nAdd(NObject *left, NObject* right);
NObject *nSubtract(NObject *left, NObject* right);
NObject *nNegate(NObject *right);

} // namespace napkin

#endif
