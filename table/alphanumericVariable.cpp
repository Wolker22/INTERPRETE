#ifndef _ALPHANUMERICVARIABLE_HPP_
#define _ALPHANUMERICVARIABLE_HPP_

#include <string>
#include "variable.hpp"

namespace lp {

class AlphanumericVariable : public Variable {
private:
    std::string _value;

public:
    // Constructor mejorado con valores por defecto
    explicit AlphanumericVariable(const std::string& name = "", 
                                 int token = 0, 
                                 int type = ALPHANUMERIC, 
                                 const std::string& value = "")
        : Variable(name, token, type), _value(value) {}
    
    // Constructor de copia
    AlphanumericVariable(const AlphanumericVariable& other)
        : Variable(other), _value(other._value) {}

    // Destructor virtual
    virtual ~AlphanumericVariable() = default;

    // Observador
    std::string getValue() const { return _value; }

    // Modificador
    void setValue(const std::string& value) { _value = value; }

    // Sobrecarga de operadores
    AlphanumericVariable& operator=(const AlphanumericVariable& other);

    // Funciones de E/S (opcionales, podrían eliminarse si no se usan)
    void read() override;
    void write() const override;
};

} // namespace lp

#endif