#ifndef NAPKIN_ENVIRONMENT_H_
#define NAPKIN_ENVIRONMENT_H_

#include <string>
#include <unordered_map>

#include "nobject.h"
#include "nexception.h"

namespace napkin {

/**
 * Stores mappings of names to values and offers methods to bind and
 * lookup names.
 */
class Environment {
public:
  Environment() { enclosing = nullptr; };
  Environment(Environment *t_enclosing) : enclosing(t_enclosing){};
  void bind(std::string name, NObject *value);
  NObject *lookup(std::string name);
private:
  // Hash map of names to napkin objects
  // It is important that the keys are strings and not tokens since names
  // are mapped independent of location
  std::unordered_map<std::string, NObject *> map;

  // The environment "outside" the current block
  // If lookup fails inside the inner scope, we search incrementally outward
  Environment *enclosing;

  // Helpers
  bool existsSomewhere(std::string name);
};

} // namespace napkin

#endif
