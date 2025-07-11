#include "symbol.hpp"

namespace lp {

// Función auxiliar para convertir a minúsculas
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

} // namespace lp