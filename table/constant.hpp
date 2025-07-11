#ifndef _CONSTANT_HPP_
#define _CONSTANT_HPP_

#include <string>
#include <iostream>
#include <stdexcept>
#include "symbol.hpp"

namespace lp {

// Tipos de constantes
enum ConstantType {
    NUMERIC_CONSTANT,
    LOGICAL_CONSTANT,
    ALPHANUMERIC_CONSTANT,
    UNKNOWN_CONSTANT
};

class Constant : public Symbol {
public:
    Constant(const std::string& name = "", int token = 0, ConstantType type = UNKNOWN_CONSTANT)
        : Symbol(name, token), _type(type) {}
    
    Constant(const Constant& other) 
        : Symbol(other), _type(other._type) {}
    
    virtual ~Constant() = default;
    
    ConstantType getType() const { return _type; }
    void setType(ConstantType type) { _type = type; }
    
    // Métodos para obtener valores (puros virtuales)
    virtual double getNumericValue() const {
        throw std::runtime_error("Not a numeric constant");
    }
    
    virtual bool getLogicalValue() const {
        throw std::runtime_error("Not a logical constant");
    }
    
    virtual std::string getStringValue() const {
        throw std::runtime_error("Not an alphanumeric constant");
    }
    
    // Operador de asignación
    virtual Constant& operator=(const Constant& c);
    
    // Funciones de E/S
    virtual void read() = 0;
    virtual void write() const = 0;

protected:
    ConstantType _type;
};

} // namespace lp

#endif