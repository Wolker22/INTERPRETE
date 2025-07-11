#ifndef _NUMERICCONSTANT_HPP_
#define _NUMERICCONSTANT_HPP_

#include "constant.hpp"

namespace lp {

class NumericConstant : public Constant {
private:
    double _value;

public:
    // Constructor simplificado
    explicit NumericConstant(const std::string& name = "", 
                            double value = 0.0,
                            int token = 0)
        : Constant(name, token, NUMERIC_CONSTANT), _value(value) {}
    
    // Constructor de copia
    NumericConstant(const NumericConstant& other) = default;
    
    // Destructor
    ~NumericConstant() override = default;
    
    // Observadores
    double getValue() const { return _value; }
    double getNumericValue() const override { return _value; }
    
    // Modificador
    void setValue(double value) { _value = value; }
    
    // Funciones de E/S
    void read() override;
    void write() const override;
    
    // Operador de asignación
    NumericConstant& operator=(const NumericConstant& other);
};

} // namespace lp

#endif