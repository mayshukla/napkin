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
 * Returns nullptr if name is not bound.
 */
NObject *Environment::lookup(std::string name) {
  try {
    return map.at(name);
  }
  catch (std::out_of_range) {
    return nullptr;
  }
}

} // namespace napkin
