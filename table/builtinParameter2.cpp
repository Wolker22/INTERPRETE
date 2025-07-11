#include "builtinParameter2.hpp"

namespace lp {

BuiltinParameter2 &BuiltinParameter2::operator=(const BuiltinParameter2 &b) {
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