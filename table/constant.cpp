#include "constant.hpp"

namespace lp {

Constant &Constant::operator=(const Constant &c) {
    if (this != &c) {
        Symbol::operator=(c);
        _type = c._type;
    }
    return *this;
}

} // namespace lp