#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_

#include <string>
#include <memory>
#include "symbol.hpp"

namespace lp {

// Tipos de variables
enum VariableType {
    NUMERIC,
    LOGICAL,
    ALPHANUMERIC,
    UNKNOWN
};

class Variable : public Symbol {
public:
    // Constructor simplificado
    explicit Variable(const std::string& name = "", 
                     int token = 0,
                     VariableType type = UNKNOWN)
        : Symbol(name, token), _type(type) {}
    
    // Constructor de copia
    Variable(const Variable& other) = default;
    
    // Destructor virtual
    virtual ~Variable() = default;
    
    // Observadores
    VariableType getType() const { return _type; }
    
    // Métodos virtuales puros para acceso a valores
    virtual double getNumericValue() const = 0;
    virtual bool getLogicalValue() const = 0;
    virtual std::string getStringValue() const = 0;
    
    // Métodos virtuales puros para modificación de valores
    virtual void setValue(double value) = 0;
    virtual void setValue(bool value) = 0;
    virtual void setValue(const std::string& value) = 0;
    
    // Funciones de E/S (opcionales)
    virtual void read() = 0;
    virtual void write() const = 0;

protected:
    void setType(VariableType type) { _type = type; }
    
private:
    VariableType _type;
};

} // namespace lp

#endif