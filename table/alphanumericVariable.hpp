#include <iostream>
#include "alphanumericVariable.hpp"

namespace lp {

void AlphanumericVariable::read() {
    std::cout << "Name of the AlphanumericVariable: ";
    std::cin >> this->_name;
    
    std::cout << "Value of the AlphanumericVariable: ";
    std::cin >> this->_value;
}

void AlphanumericVariable::write() const {
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Type: " << this->getType() << std::endl;
    std::cout << "Value: " << this->_value << std::endl;
}

AlphanumericVariable& AlphanumericVariable::operator=(const AlphanumericVariable& other) {
    if (this != &other) {
        Variable::operator=(other);
        _value = other._value;
    }
    return *this;
}

} // namespace lp