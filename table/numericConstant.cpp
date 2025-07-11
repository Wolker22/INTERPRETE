#include <iostream>
#include "numericConstant.hpp"

namespace lp {

NumericConstant &NumericConstant::operator=(const NumericConstant &other) {
    if (this != &other) {
        Constant::operator=(other);
        _value = other._value;
    }
    return *this;
}

void NumericConstant::read() {
    std::cout << "Name of the NumericConstant: ";
    std::cin >> this->_name;
    
    std::cout << "Value of the NumericConstant: ";
    std::cin >> this->_value;
    std::cin.ignore();  // Limpiar buffer
}

void NumericConstant::write() const {
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Type: Numeric" << std::endl;
    std::cout << "Value: " << this->_value << std::endl;
}

} // namespace lp