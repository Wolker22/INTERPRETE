#include <iostream>
#include "keyword.hpp"

namespace lp {

Keyword &Keyword::operator=(const Keyword &other) {
    if (this != &other) {
        // Copiar miembros de la clase base
        Symbol::operator=(other);
    }
    return *this;
}

void Keyword::read() {
    // Solo para depuración
    std::cout << "Name of the Keyword: ";
    std::cin >> this->_name;

    std::cout << "Token of the Keyword: ";
    std::cin >> this->_token;
    std::cin.ignore();  // Limpiar el buffer
}

void Keyword::write() const {
    // Solo para depuración
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Token: " << this->getToken() << std::endl;
}

} // namespace lp