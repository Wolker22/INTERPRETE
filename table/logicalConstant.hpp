#ifndef _LOGICALCONSTANT_HPP_
#define _LOGICALCONSTANT_HPP_

#include "constant.hpp"

namespace lp {

class LogicalConstant : public Constant {
private:
    bool _value;

public:
    using Constant::operator=;

    // Constructor mejorado
    LogicalConstant(const std::string& name, int token, int type, bool value)
        : Constant(name, token, type), _value(value) {}
    
    // Constructor simplificado
    explicit LogicalConstant(const std::string& name = "", bool value = true)
        : Constant(name, CONSTANT, LOGICAL_CONSTANT), _value(value) {}
    
    // Destructor
    ~LogicalConstant() override = default;
    
    // Observadores
    bool getValue() const { return _value; }
    bool getLogicalValue() const override { return _value; }
    
    // Modificador
    void setValue(bool value) { _value = value; }
    
    // Implementación de funciones virtuales
    double getNumericValue() const override {
        return _value ? 1.0 : 0.0;
    }
    
    std::string getStringValue() const override {
        return _value ? "true" : "false";
    }
    
    void setValue(double) override {
        throw std::runtime_error("Cannot modify constant value");
    }
    
    void setValue(const std::string&) override {
        throw std::runtime_error("Cannot modify constant value");
    }
    
    // Funciones de E/S
    void read() override;
    void write() const override;
    
    // Operador de asignación
    LogicalConstant& operator=(const LogicalConstant& other);
};

} // namespace lp

#endif