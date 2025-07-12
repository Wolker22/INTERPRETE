#include <iostream>
#include <stdexcept>
#include "logicalConstant.hpp"

namespace lp {

LogicalConstant &LogicalConstant::operator=(const LogicalConstant &other) {
    if (this != &other) {
        Constant::operator=(other);
        _value = other._value;
    }
    return *this;
}

void LogicalConstant::read() {
    std::cout << "Name of the LogicalConstant: ";
    std::cin >> this->_name;
    
    std::cout << "Value of the LogicalConstant (0/1): ";
    int temp;
    std::cin >> temp;
    _value = (temp != 0);
    std::cin.ignore();  // Limpiar buffer
}

void LogicalConstant::write() const {
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Type: Logical" << std::endl;
    std::cout << "Value: " << (_value ? "true" : "false") << std::endl;
}

} // namespace lp