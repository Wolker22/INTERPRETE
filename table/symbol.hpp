#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <string>
#include "symbolInterface.hpp"

namespace lp {

class Symbol : public SymbolInterface {
protected:
    std::string _name;    // Nombre del símbolo
    int _token;           // Token del símbolo

public:
    // Constructor con inicialización por lista
    explicit Symbol(const std::string& name = "", int token = 0)
        : _name(name), _token(token) {}
    
    // Constructor de copia
    Symbol(const Symbol& other) = default;
    
    // Destructor virtual
    virtual ~Symbol() = default;
    
    // Observadores
    const std::string& getName() const { return _name; }
    int getToken() const { return _token; }
    
    // Modificadores
    void setName(const std::string& name) { _name = name; }
    void setToken(int token) { _token = token; }
    
    // Operadores relacionales
    bool operator==(const Symbol& other) const {
        // Comparación insensible a mayúsculas/minúsculas
        return toLower(_name) == toLower(other._name);
    }
    
    bool operator<(const Symbol& other) const {
        // Orden lexicográfico insensible a mayúsculas/minúsculas
        return toLower(_name) < toLower(other._name);
    }
};

} // namespace lp

#endif