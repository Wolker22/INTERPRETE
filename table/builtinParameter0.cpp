#include "builtinParameter0.hpp"

namespace lp {

BuiltinParameter0 &BuiltinParameter0::operator=(const BuiltinParameter0 &b) {
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