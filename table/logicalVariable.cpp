#include <iostream>
#include "logicalVariable.hpp"

namespace lp {

LogicalVariable &LogicalVariable::operator=(const LogicalVariable &other) {
    if (this != &other) {
        Variable::operator=(other);
        _value = other._value;
    }
    return *this;
}

void LogicalVariable::read() {
    std::cout << "Name of the LogicalVariable: ";
    std::cin >> this->_name;
    
    std::cout << "Value of the LogicalVariable (0/1): ";
    int temp;
    std::cin >> temp;
    _value = (temp != 0);
    std::cin.ignore();  // Limpiar buffer
}

void LogicalVariable::write() const {
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Type: Logical" << std::endl;
    std::cout << "Value: " << (_value ? "true" : "false") << std::endl;
}

} // namespace lp