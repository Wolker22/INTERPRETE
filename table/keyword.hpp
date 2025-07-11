#ifndef _KEYWORD_HPP_
#define _KEYWORD_HPP_

#include <string>
#include "symbol.hpp"

namespace lp {

class Keyword : public Symbol {
public:
    // Constructor con valores por defecto
    Keyword(const std::string& name = "", int token = 0)
        : Symbol(name, token) {}
    
    // Constructor de copia
    Keyword(const Keyword& other) 
        : Symbol(other) {}
    
    // Operador de asignación
    Keyword& operator=(const Keyword& other);
    
    // Destructor virtual
    virtual ~Keyword() = default;
    
    // Funciones de E/S (opcionales, podrían eliminarse)
    void write() const;
    void read();
};

} // namespace lp

#endif