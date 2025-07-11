#include "builtin.hpp"

namespace lp {

Builtin &Builtin::operator=(const Builtin &b) {
    if (this != &b) {
        Symbol::operator=(b);
        _nParameters = b._nParameters;
    }
    return *this;
}

void Builtin::read() {
    // Implementación base (puede ser extendida)
}

void Builtin::write() const {
    // Implementación base (puede ser extendida)
}

} // namespace lp