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
    
    // Implementación de funciones virtuales puras
    double getNumericValue() const override {
        return _value ? 1.0 : 0.0;
    }
    
    std::string getStringValue() const override {
        return _value ? "true" : "false";
    }
    
    void setValue(double value) override {
        _value = (value != 0.0);
    }
    
    void setValue(const std::string& value) override {
        if (value == "true" || value == "1") {
            _value = true;
        } else if (value == "false" || value == "0") {
            _value = false;
        } else {
            // Manejar error si es necesario
            _value = false;
        }
    }
    
    // Funciones de E/S
    void read() override;
    void write() const override;
    
    // Operador de asignación
    LogicalVariable& operator=(const LogicalVariable& other);
};

} // namespace lp

#endif