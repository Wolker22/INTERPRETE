#ifndef _LOGICALCONSTANT_HPP_
#define _LOGICALCONSTANT_HPP_

#include "constant.hpp"

namespace lp {

class LogicalConstant : public Constant {
private:
    bool _value;

public:

    using Constant::operator=;

    // Constructor simplificado
    explicit LogicalConstant(const std::string& name = "", 
                            bool value = true,
                            int token = 0)
        : Constant(name, token, LOGICAL_CONSTANT), _value(value) {}
    
    // Constructor de copia
    LogicalConstant(const LogicalConstant& other) = default;
    
    // Destructor
    ~LogicalConstant() override = default;
    
    // Observadores
    bool getValue() const { return _value; }
    bool getLogicalValue() const override { return _value; }
    
    // Modificador
    void setValue(bool value) { _value = value; }
    
    // Funciones de E/S
    void read() override;
    void write() const override;
    
    // Operador de asignación
    LogicalConstant& operator=(const LogicalConstant& other);
};

} // namespace lp

#endif