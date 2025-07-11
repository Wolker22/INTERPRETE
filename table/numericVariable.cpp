#include <iostream>
#include "numericVariable.hpp"

namespace lp {

NumericVariable &NumericVariable::operator=(const NumericVariable &other) {
    if (this != &other) {
        Variable::operator=(other);
        _value = other._value;
    }
    return *this;
}

void NumericVariable::read() {
    std::cout << "Name of the NumericVariable: ";
    std::cin >> this->_name;
    
    std::cout << "Value of the NumericVariable: ";
    std::cin >> this->_value;
    std::cin.ignore();  // Limpiar buffer
}

void NumericVariable::write() const {
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Type: Numeric" << std::endl;
    std::cout << "Value: " << this->_value << std::endl;
}

} // namespace lp