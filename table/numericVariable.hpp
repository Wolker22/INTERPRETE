#ifndef _NUMERICVARIABLE_HPP_
#define _NUMERICVARIABLE_HPP_

#include "variable.hpp"

namespace lp {

class NumericVariable : public Variable {
private:
    double _value;

public:
    // Constructor simplificado
    explicit NumericVariable(const std::string& name = "", 
                            double value = 0.0,
                            int token = 0)
        : Variable(name, token, NUMERIC), _value(value) {}
    
    // Constructor de copia
    NumericVariable(const NumericVariable& other) = default;
    
    // Destructor
    ~NumericVariable() override = default;
    
    // Observadores
    double getValue() const { return _value; }
    double getNumericValue() const override { return _value; }
    
    // Modificador
    void setValue(double value) { _value = value; }
    
    // Funciones de E/S
    void read() override;
    void write() const override;
    
    // Operador de asignación
    NumericVariable& operator=(const NumericVariable& other);
};

} // namespace lp

#endif