#ifndef _LOGICALVARIABLE_HPP_
#define _LOGICALVARIABLE_HPP_

#include "variable.hpp"

namespace lp {

class LogicalVariable : public Variable {
private:
    bool _value;

public:
    // Constructor simplificado
    explicit LogicalVariable(const std::string& name = "", 
                            bool value = false,
                            int token = 0)
        : Variable(name, token, LOGICAL), _value(value) {}
    
    // Constructor de copia
    LogicalVariable(const LogicalVariable& other) = default;
    
    // Destructor
    ~LogicalVariable() override = default;
    
    // Observadores
    bool getValue() const { return _value; }
    bool getLogicalValue() const override { return _value; }
    
    // Modificador
    void setValue(bool value) { _value = value; }
    
    // Funciones de E/S
    void read() override;
    void write() const override;
    
    // Operador de asignación
    LogicalVariable& operator=(const LogicalVariable& other);
};

} // namespace lp

#endif