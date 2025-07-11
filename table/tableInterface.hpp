#ifndef _TABLEINTERFACE_HPP_
#define _TABLEINTERFACE_HPP_

#include <string>
#include "symbol.hpp"

namespace lp {

class TableInterface {
public:
    // Destructor virtual
    virtual ~TableInterface() = default;
    
    // Observadores
    virtual bool lookupSymbol(const std::string& name) const = 0;
    virtual Symbol* getSymbol(const std::string& name) = 0;
    virtual const Symbol* getSymbol(const std::string& name) const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
    
    // Modificadores
    virtual void installSymbol(Symbol* s) = 0;
    virtual void installSymbol(std::unique_ptr<Symbol> s) = 0;
    virtual void eraseSymbol(const std::string& name) = 0;
    
    // Utilidad
    virtual void printTable() const = 0;
};

} // namespace lp

#endif