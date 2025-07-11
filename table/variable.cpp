#include <iostream>
#include "variable.hpp"

namespace lp {

Variable &Variable::operator=(const Variable &other) {
    if (this != &other) {
        Symbol::operator=(other);
        _type = other._type;
    }
    return *this;
}

} // namespace lp