#ifndef NAPKIN_NOPERATOR_H_
#define NAPKIN_NOPERATOR_H_

#include "nobject.h"
#include "RuntimeException.h"

/**
 * Defines napkin language operators on NObjects
 */

namespace napkin {

NObject *nAdd(NObject *left, NObject* right);

} // namespace napkin

#endif
