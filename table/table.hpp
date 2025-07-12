#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <map>
#include <string>
#include <memory>
#include <stdexcept> // Añadido para std::runtime_error
#include "symbol.hpp"

namespace lp {

class Table {
private:
    std::map<std::string, std::unique_ptr<Symbol>> _table;

public:
    // Constructor y destructor
    Table() = default;
    ~Table() = default;

    // Observadores
    bool lookupSymbol(const std::string& name) const;
    Symbol* getSymbol(const std::string& name);
    const Symbol* getSymbol(const std::string& name) const;
    bool isEmpty() const { return _table.empty(); }
    size_t size() const { return _table.size(); }

    // Modificadores
    void installSymbol(Symbol* s);
    void installSymbol(std::unique_ptr<Symbol> s);
    void eraseSymbol(const std::string& name);
    
    // Utilidad
    void printTable() const;
};

} // namespace lp

#endif