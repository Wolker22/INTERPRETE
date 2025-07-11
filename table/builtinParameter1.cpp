#include "builtinParameter1.hpp"

namespace lp {

BuiltinParameter1 &BuiltinParameter1::operator=(const BuiltinParameter1 &b) {
    if (this != &b) {
        // Copiar miembros de la clase base
        Builtin::operator=(b);
        
        // Copiar miembros específicos
        _funcType = b._funcType;
        _function = b._function;
    }
    return *this;
}

} // namespace lp





