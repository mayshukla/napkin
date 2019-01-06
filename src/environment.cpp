#include "environment.h"


namespace napkin {

/**
 * Declares a new local binding if there is none, or reassignes a name to a new
 * value.
 */
void Environment::bind(std::string name, NObject *value) {
  // If the name doesn't exist anywhere, create a new local binding
  if (!existsSomewhere(name)) {
    map[name] = value;
    return;
  }

  // The name exists somewhere. Recurse until reach the environment where it
  // exists and set it there
  try {
    // throws out_of_range if key doesn't exist
    map.at(name);
    // re-binds name in current environment
    map[name] = value;
  } catch (std::out_of_range) {
    // Name not found in current environment so look in enclosing environment.
    // Enclosing cannot be nullptr since if the name exists somewhere and we
    // haven't found it yet, there must be at least one more outer environment
    if (enclosing == nullptr) {
      throw ImplementationException("in environmment.cpp: enclosing was null");
    }
    enclosing->bind(name, value);
  }
}

/**
 * Returns the value associated with name.
 * If the name hasn't been declared in this environment, with search the
 * enclosing environment. Returns nullptr if name hasn't been declared anywhere.
 */
NObject *Environment::lookup(std::string name) {
  try {
    return map.at(name);
  } catch (std::out_of_range) {
    // Name not found in current environment so look in enclosing environment.
    if (enclosing != nullptr) {
      return enclosing->lookup(name);
    }

    // The name wasn't found in the current environment and there are no
    // more enclosing environments.
    return nullptr;
  }
}

/**
 * Returns true if name exists in current environment or any outer environment
 */
bool Environment::existsSomewhere(std::string name) {
  try {
    map.at(name); // throws out_of_range if key doesn't exist
    return true;
  } catch (std::out_of_range) {
    if (enclosing != nullptr) {
      return enclosing->existsSomewhere(name);
    } else {
      // name does not exist in current environment and there are no more outer
      // environments
      return false;
    }
  }
}

} // namespace napkin
