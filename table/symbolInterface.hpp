#ifndef _SYMBOLINTERFACE_HPP_
#define _SYMBOLINTERFACE_HPP_

#include <string>
#include <stdexcept> // Añadido para std::runtime_error

namespace lp {

class SymbolInterface {
public:
    // Observadores
    virtual const std::string& getName() const = 0;
    virtual int getToken() const = 0;
    
    // Modificadores
    virtual void setName(const std::string& name) = 0;
    virtual void setToken(int token) = 0;
    
    // Destructor virtual
    virtual ~SymbolInterface() = default;
    
    // Nuevos métodos para acceso polimórfico a valores
    virtual double getNumericValue() const {
        throw std::runtime_error("Not a numeric symbol");
    }
    
    virtual bool getLogicalValue() const {
        throw std::runtime_error("Not a logical symbol");
    }
    
    virtual std::string getStringValue() const {
        throw std::runtime_error("Not an alphanumeric symbol");
    }
};

} // namespace lp

#endif