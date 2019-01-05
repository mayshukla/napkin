#include "environment.h"

namespace napkin {

/**
 * Declares a new binding if there is none, or reassignes a name to a new value.
 */
void Environment::bind(std::string name, NObject *value) {
  map[name] = value;
}

/**
 * Returns the value associated with name.
 * If the name hasn't been declared in this environment, with search the
 * enclosing environment. Returns nullptr if name hasn't been declared anywhere.
 */
NObject *Environment::lookup(std::string name) {
  try {
    return map.at(name);
  }
  catch (std::out_of_range) {
    // Name not found in current environment so look in enclosing environment.
    if (enclosing != nullptr) {
      return enclosing->lookup(name);
    }

    // The name wasn't found in the current environment and there are no
    // more enclosing environments.
    return nullptr;
  }
}

} // namespace napkin
