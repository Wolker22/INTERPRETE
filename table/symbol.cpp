#include "symbol.hpp"
#include <cctype> // Añadido para std::tolower

namespace lp {

std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

} // namespace lp